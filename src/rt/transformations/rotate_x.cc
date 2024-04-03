#include "rotate_x.hh"

#include <cmath>

#include <rt/animations/static_animation.hh>

namespace rt {

RotateX::RotateX(const Angle<>& value) noexcept
    : RotateX{std::make_unique<StaticAnimation<Angle<>>>(value)} {}

RotateX::RotateX(std::unique_ptr<Animation<Angle<>>> value) noexcept
    : angle_{std::move(value)} {
  SetTime(std::chrono::milliseconds{0});
}

const Angle<>& RotateX::angle() const noexcept {
  return angle_->Get();
}

RotateX& RotateX::SetAngle(const Angle<>& value) noexcept {
  matrix_[{1, 1}] = std::cos((*angle_)->radians());
  matrix_[{2, 1}] = std::sin((*angle_)->radians());
  matrix_[{1, 2}] = -matrix_[{2, 1}];
  matrix_[{2, 2}] = matrix_[{1, 1}];
  return *this;
}

void RotateX::SetTime(std::chrono::milliseconds time) noexcept {
  SetAngle(*angle_->SetTime(time));
}

std::unique_ptr<Transformation> RotateX::Inverse() const noexcept {
  return std::make_unique<RotateX>(-angle_->Get());
}

}  // namespace rt
