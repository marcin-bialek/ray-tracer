#include "renderer.hh"

#include <iostream>

#include <rt/lights/ambient_light.hh>
#include <rt/lights/parallel_light.hh>

namespace rt {

static constexpr auto kEpsilon = 0.0001;

std::unique_ptr<Image> Renderer::Render(const Scene& scene) {
  scene_ = &scene;
  auto camera = scene.camera();
  auto viewport = camera->viewport();
  auto du = viewport.u / camera->width();
  auto dv = viewport.v / camera->height();
  auto pixel_origin = viewport.origin + (du + dv) / 2;
  image_ = std::make_unique<Image>(camera->width(), camera->height());

  std::size_t progress = 0;
  auto total = camera->width() * camera->height();
  for (std::size_t y = 0; y < camera->height(); ++y) {
    auto row = pixel_origin + dv * y;
    for (std::size_t x = 0; x < camera->width(); ++x) {
      auto pixel = row + du * x;
      auto direction = (pixel - camera->position()).Unit();
      (*image_)[{x, y}] =
          ProcessRay({camera->position(), direction}, camera->max_bounces());
      std::cout << std::format("\rScanlines {}/{} ({} %)", y + 1,
                               camera->height(), 100 * (++progress) / total)
                << std::flush;
    }
  }
  std::cout << std::endl;
  return std::move(image_);
}

std::optional<Intersection> Renderer::Hit(const Ray& ray) {
  bool hit = false;
  Intersection inter{};
  inter.distance = std::numeric_limits<double>::infinity();
  for (auto& s : scene_->surfaces()) {
    auto i = s->Hit(ray);
    if (i.has_value() && i->distance < inter.distance) {
      hit = true;
      inter = *i;
    }
  }
  if (!hit) {
    return std::nullopt;
  }
  return inter;
}

Ray Renderer::GetReflectedRay(const Ray& ray,
                              const Intersection& intersection) {
  auto v = 2 * ray.direction.Dot(-intersection.normal) * intersection.normal +
           ray.direction;
  return Ray{intersection.point, v.Unit()}.Move(kEpsilon);
}

Ray Renderer::GetRefractedRay(const Ray& ray,
                              const Intersection& intersection) {
  auto n = intersection.material->refraction();
  if (intersection.front) {
    n = 1.0 / n;
  }
  auto V = ray.direction;
  auto N = intersection.normal;
  auto VN = V.Dot(-N);
  auto x = 1.0 - std::pow(n, 2.0) * (1.0 - std::pow(VN, 2.0));
  if (x < 0.0) {
    return Ray{intersection.point, (2 * VN * N + V).Unit()}.Move(kEpsilon);
  }
  auto T = n * (V + N * VN) - N * std::sqrt(x);
  return Ray{intersection.point, T.Unit()}.Move(kEpsilon);
}

Vector3<> Renderer::Illuminate(const Ray& ray,
                               const Intersection& intersection) {
  Vector3<> color{};
  for (auto& light : scene_->lights()) {
    auto shadow_ray = light->GetShadowRay(intersection.point);
    if (shadow_ray.has_value()) {
      auto distance = light->GetDistance(shadow_ray->origin);
      auto shadow_inter = Hit(shadow_ray->Move(kEpsilon));
      if (shadow_inter.has_value() && shadow_inter->distance < distance) {
        continue;
      }
    }
    auto x = light->Illuminate(ray, intersection);
    color += x;
  }
  return color;
}

Vector3<> Renderer::ProcessRay(const Ray& ray, std::size_t bounces) {
  auto intersection = Hit(ray);
  if (!intersection.has_value()) {
    return scene_->background();
  }
  auto color = Illuminate(ray, *intersection);
  if (bounces == 0) {
    return color;
  }
  Vector3<> reflected_color{};
  auto reflectance = intersection->material->reflectance();
  if (0.0 < reflectance) {
    auto c = ProcessRay(GetReflectedRay(ray, *intersection), bounces - 1);
    reflected_color = (reflectance * c);
  }
  Vector3<> refracted_color{};
  auto transmittance = intersection->material->transmittance();
  if (0.0 < transmittance) {
    auto c = ProcessRay(GetRefractedRay(ray, *intersection), bounces - 1);
    refracted_color = (transmittance * c);
  }
  return color * (1 - reflectance - transmittance) + reflected_color +
         refracted_color;
}

}  // namespace rt
