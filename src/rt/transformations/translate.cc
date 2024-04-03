#include "translate.hh"

#include <rt/animations/static_animation.hh>

namespace rt {

Translate::Translate(const Vector3<>& value) noexcept
    : Translate{std::make_unique<StaticAnimation<Vector3<>>>(value)} {}

Translate::Translate(std::unique_ptr<Animation<Vector3<>>> value) noexcept
    : vector_{std::move(value)} {
  SetTime(std::chrono::milliseconds{0});
}

const Vector3<>& Translate::vector() const noexcept {
  return vector_->Get();
}

Translate& Translate::SetVector(const Vector3<>& value) noexcept {
  matrix_[{0, 3}] = value.x;
  matrix_[{1, 3}] = value.y;
  matrix_[{2, 3}] = value.z;
  return *this;
}

void Translate::SetTime(std::chrono::milliseconds time) noexcept {
  SetVector(*vector_->SetTime(time));
}

std::unique_ptr<Transformation> Translate::Inverse() const noexcept {
  return std::make_unique<Translate>(-vector_->Get());
}

}  // namespace rt
