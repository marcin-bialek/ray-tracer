#pragma once

#include <rt/animations/animation.hh>
#include <rt/math/vector3.hh>

#include "transformation.hh"

namespace rt {

class Translate : public Transformation {
 public:
  explicit Translate() noexcept = default;
  explicit Translate(const Vector3<>& value) noexcept;
  explicit Translate(std::unique_ptr<Animation<Vector3<>>> value) noexcept;

  const Vector3<>& vector() const noexcept;

  Translate& SetVector(const Vector3<>& value) noexcept;
  void SetTime(const std::chrono::milliseconds& time) noexcept override;

  std::unique_ptr<Transformation> Inverse() const noexcept override;

 private:
  Vector3<> vector_{};
  std::unique_ptr<Animation<Vector3<>>> animation_{};
};

}  // namespace rt
