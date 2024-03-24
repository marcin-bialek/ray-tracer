#pragma once

#include <rt/math/vector3.hh>

#include "light.hh"

namespace rt {

class ParallelLight final : public Light {
 public:
  explicit ParallelLight() = default;

  const Vector3<>& color() const noexcept;
  const Vector3<>& direction() const noexcept;

  ParallelLight& SetColor(const Vector3<>& value) noexcept;
  ParallelLight& SetDirection(const Vector3<>& value) noexcept;

  Vector3<> Illuminate(const Ray& ray,
                       const Intersection& intersection) const override;
  std::string ToString() const override;

 public:
  Vector3<> color_;
  Vector3<> direction_;
};

}  // namespace rt
