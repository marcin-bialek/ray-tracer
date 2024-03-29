#pragma once

#include <rt/math/angle.hh>

#include "transformation.hh"

namespace rt {

class RotateY : public Transformation {
 public:
  explicit RotateY() noexcept = default;

  const Angle<>& angle() const noexcept;

  RotateY& SetAngle(const Angle<>& value) noexcept;

 private:
  Angle<> angle_;
};

}  // namespace rt
