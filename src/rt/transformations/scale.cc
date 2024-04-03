#include "scale.hh"

#include <rt/animations/static_animation.hh>

namespace rt {

Scale::Scale(const Vector3<>& value) noexcept
    : Scale{std::make_unique<StaticAnimation<Vector3<>>>(value)} {}

Scale::Scale(std::unique_ptr<Animation<Vector3<>>> value) noexcept
    : vector_{std::move(value)} {
  SetTime(std::chrono::milliseconds{0});
}

const Vector3<>& Scale::vector() const noexcept {
  return vector_->Get();
}

Scale& Scale::SetVector(const Vector3<>& value) noexcept {
  matrix_[{0, 0}] = value.x;
  matrix_[{1, 1}] = value.y;
  matrix_[{2, 2}] = value.z;
  return *this;
}

void Scale::SetTime(std::chrono::milliseconds time) noexcept {
  SetVector(*vector_->SetTime(time));
}

std::unique_ptr<Transformation> Scale::Inverse() const noexcept {
  return std::make_unique<Scale>((*vector_)->Inverse());
}

}  // namespace rt
