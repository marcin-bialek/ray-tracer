#pragma once

#include <rt/math/angle.hh>

#include "transformation.hh"

namespace rt {

class RotateZ : public Transformation {
 public:
  explicit RotateZ() noexcept = default;

  const Angle<>& angle() const noexcept;

  RotateZ& SetAngle(const Angle<>& value) noexcept;

  std::unique_ptr<Transformation> Inverse() const override;

 private:
  Angle<> angle_{};
};

}  // namespace rt
