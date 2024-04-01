#include "scale.hh"

namespace rt {

Scale::Scale(const Vector3<>& value) noexcept {
  SetVector(value);
}

Scale::Scale(std::unique_ptr<Animation<Vector3<>>> value) noexcept {
  animation_ = std::move(value);
  SetTime(std::chrono::milliseconds{0});
}

const Vector3<>& Scale::vector() const noexcept {
  return vector_;
}

Scale& Scale::SetVector(const Vector3<>& value) noexcept {
  vector_ = value;
  matrix_[{0, 0}] = vector_.x;
  matrix_[{1, 1}] = vector_.y;
  matrix_[{2, 2}] = vector_.z;
  return *this;
}

void Scale::SetTime(const std::chrono::milliseconds& time) noexcept {
  if (animation_) {
    SetVector(animation_->Get(time));
  }
}

std::unique_ptr<Transformation> Scale::Inverse() const noexcept {
  return std::make_unique<Scale>(vector_.Inverse());
}

}  // namespace rt
