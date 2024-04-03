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
  explicit Renderer(const Scene& scene) noexcept;

  std::unique_ptr<Image> Render();

 private:
  const Scene& scene_;
  const Camera& camera_;
  Viewport viewport_;

  std::optional<Intersection> Hit(const Ray& ray);
  Ray GetReflectedRay(const Ray& ray, const Intersection& intersection);
  Ray GetRefractedRay(const Ray& ray, const Intersection& intersection);
  Vector3<> Illuminate(const Ray& ray, const Intersection& intersection);
  Vector3<> ProcessRay(const Ray& ray, std::size_t bounces);
};

}  // namespace rt
