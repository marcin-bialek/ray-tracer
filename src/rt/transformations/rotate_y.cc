#include "rotate_y.hh"

#include <cmath>

#include <rt/animations/static_animation.hh>

namespace rt {

RotateY::RotateY(const Angle<>& value) noexcept
    : RotateY{std::make_unique<StaticAnimation<Angle<>>>(value)} {}

RotateY::RotateY(std::unique_ptr<Animation<Angle<>>> value) noexcept
    : angle_{std::move(value)} {
  SetTime(std::chrono::milliseconds{0});
}

const Angle<>& RotateY::angle() const noexcept {
  return angle_->Get();
}

RotateY& RotateY::SetAngle(const Angle<>& value) noexcept {
  matrix_[{0, 0}] = std::cos((*angle_)->radians());
  matrix_[{0, 2}] = std::sin((*angle_)->radians());
  matrix_[{2, 0}] = -matrix_[{0, 2}];
  matrix_[{2, 2}] = matrix_[{0, 0}];
  return *this;
}

void RotateY::SetTime(std::chrono::milliseconds time) noexcept {
  SetAngle(*angle_->SetTime(time));
}

std::unique_ptr<Transformation> RotateY::Inverse() const noexcept {
  return std::make_unique<RotateY>(-angle_->Get());
}

}  // namespace rt
