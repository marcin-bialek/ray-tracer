#pragma once

#include <rt/animations/animation.hh>
#include <rt/math/angle.hh>

#include "transformation.hh"

namespace rt {

class RotateX : public Transformation {
 public:
  explicit RotateX() noexcept = default;
  explicit RotateX(const Angle<>& value) noexcept;
  explicit RotateX(std::unique_ptr<Animation<Angle<>>> value) noexcept;

  const Angle<>& angle() const noexcept;

  RotateX& SetAngle(const Angle<>& value) noexcept;
  void SetTime(const std::chrono::milliseconds& time) noexcept override;

  std::unique_ptr<Transformation> Inverse() const noexcept override;

 private:
  Angle<> angle_{};
  std::unique_ptr<Animation<Angle<>>> animation_{};
};

}  // namespace rt
