#pragma once

#include <rt/math/vector3.hh>

#include "surface.hh"

namespace rt {

class Sphere : public Surface {
 public:
  explicit Sphere() noexcept = default;

  const Vector3<>& position() const noexcept;
  float radius() const noexcept;

  Sphere& SetPosition(const Vector3<>& value) noexcept;
  Sphere& SetRadius(float value) noexcept;

  std::string ToString() const override;

 private:
  Vector3<> position_;
  float radius_;
};

}  // namespace rt
