#include "rotate_z.hh"

namespace rt {

const Angle<>& RotateZ::angle() const noexcept {
  return angle_;
}

RotateZ& RotateZ::SetAngle(const Angle<>& value) noexcept {
  angle_ = value;
  return *this;
}

}  // namespace rt
