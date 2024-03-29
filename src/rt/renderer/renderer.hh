#pragma once

#include <memory>

#include <rt/common/image.hh>
#include <rt/scene/scene.hh>

#include "intersection.hh"
#include "ray.hh"

namespace rt {

class Renderer {
 public:
  explicit Renderer() noexcept = default;

  std::unique_ptr<Image> Render(const Scene& scene);

 private:
  const Scene* scene_;
  std::unique_ptr<Image> image_;

  std::optional<Intersection> Hit(const Ray& ray);
  Ray GetReflectedRay(const Ray& ray, const Intersection& intersection);
  Ray GetRefractedRay(const Ray& ray, const Intersection& intersection);
  Vector3<> Illuminate(const Ray& ray, const Intersection& intersection);
  Vector3<> ProcessRay(const Ray& ray, std::size_t bounces);
};

}  // namespace rt
