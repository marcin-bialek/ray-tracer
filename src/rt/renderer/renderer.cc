#include "renderer.hh"

#include <iostream>

#include <indicators/indicators.hh>

#include <rt/lights/ambient_light.hh>
#include <rt/lights/parallel_light.hh>

namespace rt {

static constexpr auto kEpsilon = 0.0001;

Renderer::Renderer(const Scene& scene) noexcept
    : scene_{scene}, camera_{scene.camera()}, viewport_{camera_.viewport()} {}

std::unique_ptr<Image> Renderer::Render() {
  auto image = std::make_unique<Image>(camera_.width(), camera_.height());

  indicators::show_console_cursor(false);
  indicators::ProgressBar bar{indicators::option::BarWidth{50},
                              indicators::option::MaxProgress{camera_.height()},
                              indicators::option::PrefixText{"Rendering "},
                              indicators::option::ShowPercentage{true},
                              indicators::option::ShowElapsedTime{true},
                              indicators::option::ShowRemainingTime{true}};

  for (std::size_t y = 0; y < camera_.height(); ++y) {
    auto row = viewport_.pixel_origin + viewport_.dv * y;
    for (std::size_t x = 0; x < camera_.width(); ++x) {
      auto pixel = row + viewport_.du * x;
      auto direction = (pixel - camera_.position()).Unit();
      auto ray = Ray{camera_.position(), direction};
      (*image)[{x, y}] = ProcessRay(ray, camera_.max_bounces());
    }
    bar.tick();
  }

  indicators::show_console_cursor(true);
  return std::move(image);
}

std::optional<Intersection> Renderer::Hit(const Ray& ray) {
  bool hit = false;
  Intersection inter{};
  inter.distance = std::numeric_limits<double>::infinity();
  for (auto& s : scene_.surfaces()) {
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
  for (auto& light : scene_.lights()) {
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
    return scene_.background();
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
