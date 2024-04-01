#include "translate.hh"

#include <iostream>

namespace rt {

Translate::Translate(const Vector3<>& value) noexcept {
  SetVector(value);
}

Translate::Translate(std::unique_ptr<Animation<Vector3<>>> value) noexcept {
  animation_ = std::move(value);
  SetTime(std::chrono::milliseconds{0});
}

const Vector3<>& Translate::vector() const noexcept {
  return vector_;
}

Translate& Translate::SetVector(const Vector3<>& value) noexcept {
  vector_ = value;
  matrix_[{0, 3}] = vector_.x;
  matrix_[{1, 3}] = vector_.y;
  matrix_[{2, 3}] = vector_.z;
  return *this;
}

void Translate::SetTime(const std::chrono::milliseconds& time) noexcept {
  if (animation_) {
    SetVector(animation_->Get(time));
  }
}

std::unique_ptr<Transformation> Translate::Inverse() const noexcept {
  return std::make_unique<Translate>(-vector_);
}

}  // namespace rt
