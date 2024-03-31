#include "scale.hh"

namespace rt {

const Vector3<>& Scale::vector() const noexcept {
  return vector_;
}

Scale& Scale::SetVector(const Vector3<>& value) noexcept {
  vector_ = value;
  matrix = Matrix4<>::Identity();
  matrix[{0, 0}] = vector_.x;
  matrix[{1, 1}] = vector_.y;
  matrix[{2, 2}] = vector_.z;
  return *this;
}

std::unique_ptr<Transformation> Scale::Inverse() const {
  auto t = std::make_unique<Scale>();
  t->SetVector({1.0 / vector_.x, 1.0 / vector_.y, 1.0 / vector_.z});
  return std::move(t);
}

}  // namespace rt
