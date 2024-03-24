#pragma once

#include <rt/math/vector3.hh>

#include "light.hh"

namespace rt {

class PointLight final : public Light {
 public:
  explicit PointLight() = default;

  const Vector3<>& color() const noexcept;
  const Vector3<>& position() const noexcept;

  PointLight& SetColor(const Vector3<>& value) noexcept;
  PointLight& SetPosition(const Vector3<>& value) noexcept;

  std::optional<Ray> GetShadowRay(const Vector3<>& origin) const override;
  Vector3<> Illuminate(const Ray& ray,
                       const Intersection& intersection) const override;
  std::string ToString() const override;

 public:
  Vector3<> color_;
  Vector3<> position_;
};

}  // namespace rt
