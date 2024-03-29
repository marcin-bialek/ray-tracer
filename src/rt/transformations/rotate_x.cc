#include "rotate_x.hh"

namespace rt {

const Angle<>& RotateX::angle() const noexcept {
  return angle_;
}

RotateX& RotateX::SetAngle(const Angle<>& value) noexcept {
  angle_ = value;
  return *this;
}

}  // namespace rt
