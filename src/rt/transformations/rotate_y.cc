#include "rotate_y.hh"

namespace rt {

const Angle<>& RotateY::angle() const noexcept {
  return angle_;
}

RotateY& RotateY::SetAngle(const Angle<>& value) noexcept {
  angle_ = value;
  return *this;
}

}  // namespace rt
