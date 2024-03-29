#pragma once

#include <rt/math/vector3.hh>

#include "transformation.hh"

namespace rt {

class Translate : public Transformation {
 public:
  explicit Translate() noexcept = default;

  const Vector3<>& vector() const noexcept;

  Translate& SetVector(const Vector3<>& value) noexcept;

 private:
  Vector3<> vector_;
};

}  // namespace rt
