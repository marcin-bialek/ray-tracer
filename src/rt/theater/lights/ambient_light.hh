#pragma once

#include <rt/math/vector3.hh>

#include "light.hh"

namespace rt {

class AmbientLight final : public Light {
 public:
  explicit AmbientLight() = default;

  const Vector3<>& color() const noexcept;

  AmbientLight& SetColor(const Vector3<>& value) noexcept;

  std::string ToString() const override;

 public:
  Vector3<> color_;
};

}  // namespace rt
