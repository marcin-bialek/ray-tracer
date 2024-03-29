#pragma once

#include <rt/math/vector3.hh>

namespace rt {

struct Ray {
  Vector3<> origin;
  Vector3<> direction;

  constexpr Ray() noexcept = default;
  constexpr Ray(const Vector3<>& origin, const Vector3<>& direction) noexcept
      : origin{origin}, direction{direction} {}

  constexpr Vector3<> At(double t) const noexcept {
    return origin + t * direction;
  }

  constexpr Ray Move(double t) const noexcept {
    return {At(t), direction};
  }
};

}  // namespace rt
