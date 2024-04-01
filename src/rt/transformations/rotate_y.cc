#include "rotate_y.hh"

#include <cmath>

namespace rt {

RotateY::RotateY(const Angle<>& value) noexcept {
  SetAngle(value);
}

RotateY::RotateY(std::unique_ptr<Animation<Angle<>>> value) noexcept {
  animation_ = std::move(value);
  SetTime(std::chrono::milliseconds{0});
}

const Angle<>& RotateY::angle() const noexcept {
  return angle_;
}

RotateY& RotateY::SetAngle(const Angle<>& value) noexcept {
  angle_ = value;
  matrix_[{0, 0}] = std::cos(angle_.radians());
  matrix_[{0, 2}] = std::sin(angle_.radians());
  matrix_[{2, 0}] = -matrix_[{0, 2}];
  matrix_[{2, 2}] = matrix_[{0, 0}];
  return *this;
}

void RotateY::SetTime(const std::chrono::milliseconds& time) noexcept {
  if (animation_) {
    SetAngle(animation_->Get(time));
  }
}

std::unique_ptr<Transformation> RotateY::Inverse() const noexcept {
  return std::make_unique<RotateY>(-angle_);
}

}  // namespace rt
