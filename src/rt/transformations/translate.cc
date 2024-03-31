#include "translate.hh"

namespace rt {

const Vector3<>& Translate::vector() const noexcept {
  return vector_;
}

Translate& Translate::SetVector(const Vector3<>& value) noexcept {
  vector_ = value;
  matrix = Matrix4<>::Identity();
  matrix[{0, 3}] = vector_.x;
  matrix[{1, 3}] = vector_.y;
  matrix[{2, 3}] = vector_.z;
  return *this;
}

std::unique_ptr<Transformation> Translate::Inverse() const {
  auto t = std::make_unique<Translate>();
  t->SetVector(-vector_);
  return std::move(t);
}

}  // namespace rt
