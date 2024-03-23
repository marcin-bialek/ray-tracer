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
  auto origin = viewport.origin + (du + dv) / 2;
  image_ = std::make_unique<Image>(camera->width(), camera->height());

  for (std::size_t y = 0; y < camera->height(); ++y) {
    for (std::size_t x = 0; x < camera->width(); ++x) {
      auto pixel_center = origin + (x * du) + (y * dv);
      auto direction = (pixel_center - camera->position()).Unit();
      (*image_)[{x, y}] = ProcessRay({camera->position(), direction});
    }
  }

  return std::move(image_);
}

Vector3<> Renderer::ProcessRay(const Ray& ray) {
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

  auto material_color = surface->material()->GetColor();
  auto light_color = Vector3<>{0.0, 0.0, 0.0};
  auto ka = surface->material()->phong().ka;
  auto kd = surface->material()->phong().kd;

  for (auto& light : scene_->lights()) {
    auto ambient = dynamic_cast<AmbientLight*>(light.get());
    if (ambient) {
      light_color += ka * ambient->color();
      continue;
    }
    auto parallel = dynamic_cast<ParallelLight*>(light.get());
    if (parallel) {
      light_color += kd *
                     std::max(0.0, parallel->direction().Dot(-inter.normal)) *
                     parallel->color();
      continue;
    }
  }

  return material_color.Hadamard(light_color).Clamp(0.0, 1.0);
}

}  // namespace rt
