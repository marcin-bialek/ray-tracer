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

Vector3<> Renderer::ProcessRay(const Ray& ray, std::size_t bounces) {
  if (bounces == 0) {
    return scene_->background();
  }
  Surface* surface = nullptr;
  Intersection inter{};
  inter.distance = std::numeric_limits<double>::infinity();
  for (auto& s : scene_->surfaces()) {
    auto i = s->Hit(ray);
    if (i.has_value() && i->distance < inter.distance) {
      surface = s.get();
      inter = *i;
    }
  }
  if (!surface) {
    return scene_->background();
  }
  auto ref = ray.direction - 2 * ray.direction.Dot(inter.normal) * inter.normal;
  auto c0 = ProcessRay({inter.point, ref}, bounces - 1);
  auto c1 = surface->material()->GetColor();
  return 0.3 * c0 + 0.7 * c1;
}

}  // namespace rt
