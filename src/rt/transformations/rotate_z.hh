#pragma once

#include <rt/math/angle.hh>

#include "transformation.hh"

namespace rt {

class RotateZ : public Transformation {
 public:
  explicit RotateZ() noexcept = default;

  const Angle<>& angle() const noexcept;

  RotateZ& SetAngle(const Angle<>& value) noexcept;

 private:
  Angle<> angle_;
};

}  // namespace rt
