#include "rotate_x.hh"

#include <cmath>

namespace rt {

RotateX::RotateX(const Angle<>& value) noexcept {
  SetAngle(value);
}

RotateX::RotateX(std::unique_ptr<Animation<Angle<>>> value) noexcept {
  animation_ = std::move(value);
  SetTime(std::chrono::milliseconds{0});
}

const Angle<>& RotateX::angle() const noexcept {
  return angle_;
}

RotateX& RotateX::SetAngle(const Angle<>& value) noexcept {
  angle_ = value;
  matrix_[{1, 1}] = std::cos(angle_.radians());
  matrix_[{2, 1}] = std::sin(angle_.radians());
  matrix_[{1, 2}] = -matrix_[{2, 1}];
  matrix_[{2, 2}] = matrix_[{1, 1}];
  return *this;
}

void RotateX::SetTime(const std::chrono::milliseconds& time) noexcept {
  if (animation_) {
    SetAngle(animation_->Get(time));
  }
}

std::unique_ptr<Transformation> RotateX::Inverse() const noexcept {
  return std::make_unique<RotateX>(-angle_);
}

}  // namespace rt
