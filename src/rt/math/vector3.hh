#pragma once

#include <cmath>

namespace rt {

template <typename Tp = float>
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
};

template <typename Tp>
constexpr Vector3<Tp> operator+(const Vector3<Tp>& a,
                                const Vector3<Tp>& b) noexcept {
  return a.Add(b);
}

template <typename Tp>
constexpr Vector3<Tp> operator-(const Vector3<Tp>& a) noexcept {
  return {-a.x, -a.y, -a.z};
}

template <typename Tp>
constexpr Vector3<Tp> operator-(const Vector3<Tp>& a,
                                const Vector3<Tp>& b) noexcept {
  return a.Substract(b);
}

template <typename Tp>
constexpr Vector3<Tp> operator*(Tp s, const Vector3<Tp>& v) noexcept {
  return {s * v.x, s * v.y, s * v.z};
}

template <typename Tp>
constexpr Vector3<Tp> operator*(const Vector3<Tp>& v, Tp s) noexcept {
  return {s * v.x, s * v.y, s * v.z};
}

}  // namespace rt
