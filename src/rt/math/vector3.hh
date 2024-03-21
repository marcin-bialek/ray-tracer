#pragma once

#include <cmath>
#include <format>

#include <rt/common/concepts.hh>

namespace rt {

template <Numeric Tp = double>
struct Vector3 {
  Tp x{};
  Tp y{};
  Tp z{};

  constexpr Vector3() noexcept {}
  constexpr Vector3(Tp x, Tp y, Tp z) noexcept : x{x}, y{y}, z{z} {}

  Tp Length() const noexcept {
    return std::sqrt(x * x + y * y + z * z);
  }

  constexpr Vector3<Tp> Add(const Vector3<Tp>& v) const noexcept {
    return {x + v.x, y + v.y, z + v.z};
  }

  constexpr Vector3<Tp> Substract(const Vector3<Tp>& v) const noexcept {
    return {x - v.x, y - v.y, z - v.z};
  }

  constexpr Tp Dot(const Vector3<Tp>& v) const noexcept {
    return (x * v.x) + (y * v.y) + (z * v.z);
  }

  constexpr Vector3<Tp> Cross(const Vector3<Tp>& v) const noexcept {
    return {
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x,
    };
  }

  std::string ToString() const {
    return std::format("{{{:.2f}, {:.2f}, {:.2f}}}", x, y, z);
  }
};

template <Numeric Tp>
constexpr Vector3<Tp> operator+(const Vector3<Tp>& a,
                                const Vector3<Tp>& b) noexcept {
  return a.Add(b);
}

template <Numeric Tp>
constexpr Vector3<Tp> operator-(const Vector3<Tp>& a) noexcept {
  return {-a.x, -a.y, -a.z};
}

template <Numeric Tp>
constexpr Vector3<Tp> operator-(const Vector3<Tp>& a,
                                const Vector3<Tp>& b) noexcept {
  return a.Substract(b);
}

template <Numeric Tp>
constexpr Vector3<Tp> operator*(Tp s, const Vector3<Tp>& v) noexcept {
  return {s * v.x, s * v.y, s * v.z};
}

template <Numeric Tp>
constexpr Vector3<Tp> operator*(const Vector3<Tp>& v, Tp s) noexcept {
  return {s * v.x, s * v.y, s * v.z};
}

template <Numeric Tp>
constexpr Vector3<Tp> operator*(const Vector3<Tp>& a,
                                const Vector3<Tp>& b) noexcept {
  return a.Cross(b);
}

}  // namespace rt
