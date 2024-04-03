#pragma once

#include <chrono>
#include <memory>

#include <rt/math/matrix4.hh>

namespace rt {

class Transformation {
 public:
  virtual ~Transformation() noexcept = default;
  virtual void SetTime(std::chrono::milliseconds time) noexcept = 0;
  virtual std::unique_ptr<Transformation> Inverse() const noexcept = 0;

  inline const Matrix4<>& GetMatrix() const noexcept {
    return matrix_;
  }

 protected:
  Matrix4<> matrix_{};
};

constexpr Matrix4<> operator*(const Transformation& a,
                              const Transformation& b) noexcept {
  return a.GetMatrix() * b.GetMatrix();
}

constexpr Matrix4<> operator*(const Matrix4<>& a,
                              const Transformation& b) noexcept {
  return a * b.GetMatrix();
}

constexpr Matrix4<> operator*(const Transformation& a,
                              const Matrix4<>& b) noexcept {
  return a.GetMatrix() * b;
}

}  // namespace rt
