#include "scale.hh"

namespace rt {

const Vector3<>& Scale::vector() const noexcept {
  return vector_;
}

Scale& Scale::SetVector(const Vector3<>& value) noexcept {
  vector_ = value;
  return *this;
}

}  // namespace rt
