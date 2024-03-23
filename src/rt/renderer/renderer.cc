#include "renderer.hh"

#include <iostream>

#include <rt/theater/lights/ambient_light.hh>
#include <rt/theater/lights/parallel_light.hh>

namespace rt {

std::unique_ptr<Image> Renderer::Render(const Scene& scene) {
  auto camera = scene.camera();
  scene_ = &scene;
  image_ = std::make_unique<Image>(camera->width(), camera->height());

  auto aspect_ratio = static_cast<double>(camera->height()) /
                      static_cast<double>(camera->width());
  auto focal_length = (camera->position() - camera->lookat()).Length();
  auto h = std::tan(camera->horizontal_fov().radians());
  auto viewport_width = 2 * h * focal_length;
  auto viewport_height = aspect_ratio * viewport_width;

  auto w = (camera->position() - camera->lookat()).Unit();
  auto u = (camera->up() * w).Unit();
  auto v = w * u;

  auto viewport_u = viewport_width * u;
  auto viewport_v = viewport_height * -v;

  auto du = viewport_u / camera->width();
  auto dv = viewport_v / camera->height();

  auto viewport_origin = camera->position() - (focal_length * w) -
                         (viewport_u / 2) - (viewport_v / 2);
  auto pixel_origin = viewport_origin + (du + dv) / 2;

  for (std::size_t y = 0; y < camera->height(); ++y) {
    for (std::size_t x = 0; x < camera->width(); ++x) {
      auto pixel_center = pixel_origin + (x * du) + (y * dv);
      auto direction = (pixel_center - camera->position()).Unit();
      (*image_)[{x, y}] = ProcessRay({camera->position(), direction});
    }
  }

  return std::move(image_);
}

Vector3<> Renderer::ProcessRay(const Ray& ray) {
  Surface* surface = nullptr;
  auto distance = std::numeric_limits<double>::infinity();
  for (auto& s : scene_->surfaces()) {
    auto d = s->Intersection(ray);
    if (0 <= d && d < distance) {
      surface = s.get();
      distance = d;
    }
  }
  if (!surface) {
    return scene_->background();
  }

  auto normal = surface->Normal(ray.At(distance));
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
      light_color += kd * std::max(0.0, parallel->direction().Dot(-normal)) *
                     parallel->color();
      continue;
    }
  }

  return material_color.Hadamard(light_color).Clamp(0.0, 1.0);
}

}  // namespace rt
