#include "scale.hh"

namespace rt {

Scale::Scale(const Vector3<>& value) noexcept {
  SetVector(value);
}

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
  return std::make_unique<Scale>(vector_.Inverse());
}

}  // namespace rt
