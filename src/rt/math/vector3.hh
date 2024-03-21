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

  Vector3<Tp> Unit() const noexcept {
    auto l = Length();
    return {x / l, y / l, z / l};
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

template <Numeric Tp, Numeric Up>
constexpr Vector3<Tp> operator*(Up s, const Vector3<Tp>& v) noexcept {
  return {
      static_cast<Tp>(s * v.x),
      static_cast<Tp>(s * v.y),
      static_cast<Tp>(s * v.z),
  };
}

template <Numeric Tp, Numeric Up>
constexpr Vector3<Tp> operator*(const Vector3<Tp>& v, Up s) noexcept {
  return s * v;
}

template <Numeric Tp, Numeric Up>
constexpr Vector3<Tp> operator/(const Vector3<Tp>& v, Up s) noexcept {
  return {
      static_cast<Tp>(v.x / s),
      static_cast<Tp>(v.y / s),
      static_cast<Tp>(v.z / s),
  };
}

template <Numeric Tp>
constexpr Vector3<Tp> operator*(const Vector3<Tp>& a,
                                const Vector3<Tp>& b) noexcept {
  return a.Cross(b);
}

}  // namespace rt
