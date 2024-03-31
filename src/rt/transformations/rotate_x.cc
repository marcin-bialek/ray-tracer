#include "rotate_x.hh"

#include <cmath>

namespace rt {

RotateX::RotateX(const Angle<>& value) noexcept {
  SetAngle(value);
}

const Angle<>& RotateX::angle() const noexcept {
  return angle_;
}

RotateX& RotateX::SetAngle(const Angle<>& value) noexcept {
  angle_ = value;
  matrix = Matrix4<>::Identity();
  matrix[{1, 1}] = std::cos(angle_.radians());
  matrix[{2, 1}] = std::sin(angle_.radians());
  matrix[{1, 2}] = -matrix[{2, 1}];
  matrix[{2, 2}] = matrix[{1, 1}];
  return *this;
}

std::unique_ptr<Transformation> RotateX::Inverse() const {
  return std::make_unique<RotateX>(-angle_);
}

}  // namespace rt
