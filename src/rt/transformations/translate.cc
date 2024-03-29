#include "translate.hh"

namespace rt {

const Vector3<>& Translate::vector() const noexcept {
  return vector_;
}

Translate& Translate::SetVector(const Vector3<>& value) noexcept {
  vector_ = value;
  return *this;
}

}  // namespace rt
