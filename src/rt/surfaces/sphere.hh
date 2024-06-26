#pragma once

#include <rt/math/vector3.hh>

#include "surface.hh"

namespace rt {

class Sphere : public Surface {
 public:
  explicit Sphere() noexcept = default;

  const Vector3<>& position() const noexcept;
  double radius() const noexcept;

  Sphere& SetPosition(const Vector3<>& value) noexcept;
  Sphere& SetRadius(double value) noexcept;

  std::string ToString() const override;

 protected:
  std::optional<Intersection> DoHit(const Ray& ray) const override;

 private:
  Vector3<> position_;
  double radius_;
};

}  // namespace rt
