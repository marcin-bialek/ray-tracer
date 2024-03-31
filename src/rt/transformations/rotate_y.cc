#include "rotate_y.hh"

#include <cmath>

namespace rt {

const Angle<>& RotateY::angle() const noexcept {
  return angle_;
}

RotateY& RotateY::SetAngle(const Angle<>& value) noexcept {
  angle_ = value;
  matrix = Matrix4<>::Identity();
  matrix[{0, 0}] = std::cos(angle_.radians());
  matrix[{0, 2}] = std::sin(angle_.radians());
  matrix[{2, 0}] = -matrix[{0, 2}];
  matrix[{2, 2}] = matrix[{0, 0}];
  return *this;
}

std::unique_ptr<Transformation> RotateY::Inverse() const {
  auto t = std::make_unique<RotateY>();
  t->SetAngle(-angle_);
  return std::move(t);
}

}  // namespace rt
