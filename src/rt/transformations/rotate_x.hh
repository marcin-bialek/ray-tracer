#pragma once

#include <rt/math/angle.hh>

#include "transformation.hh"

namespace rt {

class RotateX : public Transformation {
 public:
  explicit RotateX() noexcept = default;

  const Angle<>& angle() const noexcept;

  RotateX& SetAngle(const Angle<>& value) noexcept;

 private:
  Angle<> angle_;
};

}  // namespace rt
