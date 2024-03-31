#include "rotate_z.hh"

namespace rt {

RotateZ::RotateZ(const Angle<>& value) noexcept {
  SetAngle(value);
}

const Angle<>& RotateZ::angle() const noexcept {
  return angle_;
}

RotateZ& RotateZ::SetAngle(const Angle<>& value) noexcept {
  angle_ = value;
  matrix = Matrix4<>::Identity();
  matrix[{0, 0}] = std::cos(angle_.radians());
  matrix[{1, 0}] = std::sin(angle_.radians());
  matrix[{0, 1}] = -matrix[{1, 0}];
  matrix[{1, 1}] = matrix[{0, 0}];
  return *this;
}

std::unique_ptr<Transformation> RotateZ::Inverse() const {
  return std::make_unique<RotateZ>(-angle_);
}

}  // namespace rt
