#pragma once

#include <optional>
#include <string>

#include <rt/renderer/intersection.hh>
#include <rt/renderer/ray.hh>

namespace rt {

class Light {
 public:
  virtual ~Light() noexcept = default;

  virtual double GetDistance(const Vector3<>& origin) const = 0;
  virtual std::optional<Ray> GetShadowRay(const Vector3<>& origin) const = 0;
  virtual Vector3<> Illuminate(const Ray& ray,
                               const Intersection& intersection) const = 0;
  virtual std::string ToString() const = 0;
};

}  // namespace rt
