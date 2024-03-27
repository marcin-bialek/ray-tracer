#pragma once

#include <rt/math/angle.hh>
#include <rt/math/vector3.hh>

#include "light.hh"

namespace rt {

class SpotLight final : public Light {
 public:
  explicit SpotLight() = default;

  const Vector3<>& color() const noexcept;
  const Vector3<>& position() const noexcept;
  const Vector3<>& direction() const noexcept;
  const Angle<>& falloff_a1() const noexcept;
  const Angle<>& falloff_a2() const noexcept;

  SpotLight& SetColor(const Vector3<>& value) noexcept;
  SpotLight& SetPosition(const Vector3<>& value) noexcept;
  SpotLight& SetDirection(const Vector3<>& value) noexcept;
  SpotLight& SetFallof(const Angle<>& a1, const Angle<>& a2) noexcept;

  double GetDistance(const Vector3<>& origin) const override;
  std::optional<Ray> GetShadowRay(const Vector3<>& origin) const override;
  Vector3<> Illuminate(const Ray& ray,
                       const Intersection& intersection) const override;
  std::string ToString() const override;

 public:
  Vector3<> color_;
  Vector3<> position_;
  Vector3<> direction_;
  Angle<> falloff_a1_;
  Angle<> falloff_a2_;
};

}  // namespace rt
