#pragma once

#include <rt/common/color.hh>
#include <rt/math/vector3.hh>

#include "light.hh"

namespace rt {

class PointLight final : public Light {
 public:
  explicit PointLight() = default;

  const Color& color() const noexcept;
  const Vector3<>& position() const noexcept;

  PointLight& SetColor(const Color& value) noexcept;
  PointLight& SetPosition(const Vector3<>& value) noexcept;

  std::string ToString() const override;

 public:
  Color color_;
  Vector3<> position_;
};

}  // namespace rt
