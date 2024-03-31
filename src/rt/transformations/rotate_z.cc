#include "rotate_z.hh"

namespace rt {

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
  auto t = std::make_unique<RotateZ>();
  t->SetAngle(-angle_);
  return std::move(t);
}

}  // namespace rt
