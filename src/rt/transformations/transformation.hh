#pragma once

#include <memory>

#include <rt/common/exception.hh>
#include <rt/math/matrix4.hh>
#include <rt/math/vector3.hh>

namespace rt {

class Transformation {
 public:
  constexpr explicit Transformation() noexcept
      : matrix{Matrix4<>::Identity()} {}
  constexpr explicit Transformation(const Matrix4<>& matrix) noexcept
      : matrix{matrix} {}
  constexpr virtual ~Transformation() noexcept = default;

  constexpr Vector3<> ApplyPoint(const Vector3<>& v) const noexcept {
    return matrix.MultiplyPoint(v);
  }

  constexpr Vector3<> ApplyVector(const Vector3<>& v) const noexcept {
    return matrix.MultiplyVector(v);
  }

  virtual inline std::unique_ptr<Transformation> Inverse() const {
    throw RuntimeError{"inverse of a general transformation not implemented"};
  }

  Matrix4<> matrix;
};

constexpr Transformation operator*(const Transformation& a,
                                   const Transformation& b) noexcept {
  return Transformation{a.matrix * b.matrix};
}

constexpr Transformation operator*(const Matrix4<>& a,
                                   const Transformation& b) noexcept {
  return Transformation{a * b.matrix};
}

constexpr Transformation operator*(const Transformation& a,
                                   const Matrix4<>& b) noexcept {
  return Transformation{a.matrix * b};
}

}  // namespace rt
