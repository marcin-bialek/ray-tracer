#include "renderer.hh"

#include <iostream>

#include <rt/theater/lights/ambient_light.hh>
#include <rt/theater/lights/parallel_light.hh>

namespace rt {

std::unique_ptr<Image> Renderer::Render(const Scene& scene) {
  scene_ = &scene;
  auto camera = scene.camera();
  auto viewport = camera->viewport();
  auto du = viewport.u / camera->width();
  auto dv = viewport.v / camera->height();
  auto pixel_origin = viewport.origin + (du + dv) / 2;
  image_ = std::make_unique<Image>(camera->width(), camera->height());

  for (std::size_t y = 0; y < camera->height(); ++y) {
    auto row = pixel_origin + dv * y;
    for (std::size_t x = 0; x < camera->width(); ++x) {
      auto pixel = row + du * x;
      auto direction = (pixel - camera->position()).Unit();
      (*image_)[{x, y}] =
          ProcessRay({camera->position(), direction}, camera->max_bounces());
    }
  }

  return std::move(image_);
}

std::optional<Intersection> Renderer::Hit(const Ray& ray) {
  static constexpr auto epsilon = 0.0001;
  bool hit = false;
  Intersection inter{};
  inter.distance = std::numeric_limits<double>::infinity();
  for (auto& s : scene_->surfaces()) {
    auto i = s->Hit(ray);
    if (i.has_value() && epsilon < i->distance &&
        i->distance < inter.distance) {
      hit = true;
      inter = *i;
    }
  }
  if (!hit) {
    return std::nullopt;
  }
  return inter;
}

Vector3<> Renderer::ProcessRay(const Ray& ray, std::size_t bounces) {
  if (bounces == 0) {
    return scene_->background();
  }
  auto inter = Hit(ray);
  if (!inter.has_value()) {
    return scene_->background();
  }
  Vector3<> color{};
  for (auto& light : scene_->lights()) {
    auto shadow_ray = light->GetShadowRay(inter->point);
    if (shadow_ray.has_value()) {
      auto shadow_inter = Hit(*shadow_ray);
      if (shadow_inter.has_value()) {
        continue;
      }
    }
    color += light->Illuminate(ray, *inter);
  }
  return color.Clamp(0.0, 1.0);
}

}  // namespace rt
