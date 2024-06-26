#pragma once

#include <rt/animations/animation.hh>
#include <rt/math/vector3.hh>

#include "transformation.hh"

namespace rt {

class Translate : public Transformation {
 public:
  explicit Translate(const Vector3<>& value = {0, 0, 0}) noexcept;
  explicit Translate(std::unique_ptr<Animation<Vector3<>>> value) noexcept;

  const Vector3<>& vector() const noexcept;

  Translate& SetVector(const Vector3<>& value) noexcept;
  void SetTime(std::chrono::milliseconds time) noexcept override;

  std::unique_ptr<Transformation> Inverse() const noexcept override;

 private:
  std::unique_ptr<Animation<Vector3<>>> vector_{};
};

}  // namespace rt
