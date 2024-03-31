#pragma once

#include <rt/math/angle.hh>

#include "transformation.hh"

namespace rt {

class RotateY : public Transformation {
 public:
  explicit RotateY() noexcept = default;
  explicit RotateY(const Angle<>& value) noexcept;

  const Angle<>& angle() const noexcept;

  RotateY& SetAngle(const Angle<>& value) noexcept;

  std::unique_ptr<Transformation> Inverse() const override;

 private:
  Angle<> angle_{};
};

}  // namespace rt
