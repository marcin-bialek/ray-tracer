#include "rotate_z.hh"

namespace rt {

RotateZ::RotateZ(const Angle<>& value) noexcept {
  SetAngle(value);
}

RotateZ::RotateZ(std::unique_ptr<Animation<Angle<>>> value) noexcept {
  animation_ = std::move(value);
  SetTime(std::chrono::milliseconds{0});
}

const Angle<>& RotateZ::angle() const noexcept {
  return angle_;
}

RotateZ& RotateZ::SetAngle(const Angle<>& value) noexcept {
  angle_ = value;
  matrix_[{0, 0}] = std::cos(angle_.radians());
  matrix_[{1, 0}] = std::sin(angle_.radians());
  matrix_[{0, 1}] = -matrix_[{1, 0}];
  matrix_[{1, 1}] = matrix_[{0, 0}];
  return *this;
}

void RotateZ::SetTime(const std::chrono::milliseconds& time) noexcept {
  if (animation_) {
    SetAngle(animation_->Get(time));
  }
}

std::unique_ptr<Transformation> RotateZ::Inverse() const noexcept {
  return std::make_unique<RotateZ>(-angle_);
}

}  // namespace rt
