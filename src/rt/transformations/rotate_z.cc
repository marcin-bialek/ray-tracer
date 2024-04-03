#include "rotate_z.hh"

#include <rt/animations/static_animation.hh>

namespace rt {

RotateZ::RotateZ(const Angle<>& value) noexcept
    : RotateZ{std::make_unique<StaticAnimation<Angle<>>>(value)} {}

RotateZ::RotateZ(std::unique_ptr<Animation<Angle<>>> value) noexcept
    : angle_{std::move(value)} {
  SetTime(std::chrono::milliseconds{0});
}

const Angle<>& RotateZ::angle() const noexcept {
  return angle_->Get();
}

RotateZ& RotateZ::SetAngle(const Angle<>& value) noexcept {
  matrix_[{0, 0}] = std::cos((*angle_)->radians());
  matrix_[{1, 0}] = std::sin((*angle_)->radians());
  matrix_[{0, 1}] = -matrix_[{1, 0}];
  matrix_[{1, 1}] = matrix_[{0, 0}];
  return *this;
}

void RotateZ::SetTime(std::chrono::milliseconds time) noexcept {
  SetAngle(*angle_->SetTime(time));
}

std::unique_ptr<Transformation> RotateZ::Inverse() const noexcept {
  return std::make_unique<RotateZ>(-angle_->Get());
}

}  // namespace rt
