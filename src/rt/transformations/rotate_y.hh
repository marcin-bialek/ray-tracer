#pragma once

#include <rt/animations/animation.hh>
#include <rt/math/angle.hh>

#include "transformation.hh"

namespace rt {

class RotateY : public Transformation {
 public:
  explicit RotateY() noexcept = default;
  explicit RotateY(const Angle<>& value) noexcept;
  explicit RotateY(std::unique_ptr<Animation<Angle<>>> value) noexcept;

  const Angle<>& angle() const noexcept;

  RotateY& SetAngle(const Angle<>& value) noexcept;
  void SetTime(std::chrono::milliseconds time) noexcept override;

  std::unique_ptr<Transformation> Inverse() const noexcept override;

 private:
  std::unique_ptr<Animation<Angle<>>> angle_{};
};

}  // namespace rt
