#pragma once

#include <rt/math/vector3.hh>

#include "light.hh"

namespace rt {

class AmbientLight final : public Light {
 public:
  explicit AmbientLight() = default;

  const Vector3<>& color() const noexcept;

  AmbientLight& SetColor(const Vector3<>& value) noexcept;

  double GetDistance(const Vector3<>& origin) const override;
  std::optional<Ray> GetShadowRay(const Vector3<>& origin) const override;
  Vector3<> Illuminate(const Ray& ray,
                       const Intersection& intersection) const override;
  std::string ToString() const override;

 public:
  Vector3<> color_;
};

}  // namespace rt
