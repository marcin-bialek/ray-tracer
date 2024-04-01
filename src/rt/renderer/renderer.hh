#pragma once

#include <memory>
#include <vector>

#include <rt/common/image.hh>
#include <rt/scene/scene.hh>

#include "intersection.hh"
#include "ray.hh"

namespace rt {

class Renderer {
 public:
  explicit Renderer() noexcept = default;

  std::vector<std::unique_ptr<Image>> Render(
      const Scene& scene,
      const std::chrono::milliseconds& duration =
          std::chrono::milliseconds::zero(),
      std::size_t fps = 30);

 private:
  const Scene* scene_;
  std::chrono::milliseconds t_;

  std::optional<Intersection> Hit(const Ray& ray);
  Ray GetReflectedRay(const Ray& ray, const Intersection& intersection);
  Ray GetRefractedRay(const Ray& ray, const Intersection& intersection);
  Vector3<> Illuminate(const Ray& ray, const Intersection& intersection);
  Vector3<> ProcessRay(const Ray& ray, std::size_t bounces);
};

}  // namespace rt
