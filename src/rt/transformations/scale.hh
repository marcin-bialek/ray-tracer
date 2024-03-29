#pragma once

#include <rt/math/vector3.hh>

#include "transformation.hh"

namespace rt {

class Scale : public Transformation {
 public:
  explicit Scale() noexcept = default;

  const Vector3<>& vector() const noexcept;

  Scale& SetVector(const Vector3<>& value) noexcept;

 private:
  Vector3<> vector_;
};

}  // namespace rt
