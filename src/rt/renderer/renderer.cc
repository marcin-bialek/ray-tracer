#include "renderer.hh"

#include "ray.hh"

namespace rt {

Image Renderer::Render(const Scene& scene) {
  auto camera = scene.camera();
  Image image{camera->width(), camera->height(), scene.background()};

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
      Ray ray{camera->position(), direction};

      auto a = 0.5 * (ray.direction.y + 1.0);
      auto c = (1.0 - a) * Color{1.0, 1.0, 1.0} + a * Color{0.5, 0.7, 1.0};
      image[{x, y}] = c;
    }
  }

  return image;
}

}  // namespace rt
