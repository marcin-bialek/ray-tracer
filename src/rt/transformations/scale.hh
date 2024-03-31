#pragma once

#include <rt/math/vector3.hh>

#include "transformation.hh"

namespace rt {

class Scale : public Transformation {
 public:
  explicit Scale() noexcept = default;

  const Vector3<>& vector() const noexcept;

  Scale& SetVector(const Vector3<>& value) noexcept;

  std::unique_ptr<Transformation> Inverse() const override;

 private:
  Vector3<> vector_{};
};

}  // namespace rt
