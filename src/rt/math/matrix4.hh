#pragma once

#include <array>
#include <format>
#include <tuple>

#include <rt/common/concepts.hh>

#include "vector3.hh"

namespace rt {

template <Numeric Tp = double>
struct Matrix4 {
  std::array<std::array<Tp, 4>, 4> data{};

  constexpr Matrix4() noexcept = default;

  static constexpr Matrix4<Tp> Identity() noexcept {
    Matrix4<Tp> m{};
    for (std::size_t r = 0; r < 4; ++r) {
      for (std::size_t c = 0; c < 4; ++c) {
        m.data[r][c] = r == c ? 1 : 0;
      }
    }
    return m;
  }

  constexpr const Tp& operator[](
      const std::pair<std::size_t, std::size_t>& index) const noexcept {
    return data[index.first][index.second];
  }

  constexpr Tp& operator[](
      const std::pair<std::size_t, std::size_t>& index) noexcept {
    return data[index.first][index.second];
  }

  constexpr const Tp& get(std::size_t r, std::size_t c) const noexcept {
    return data[r][c];
  }

  constexpr Tp& get(std::size_t r, std::size_t c) noexcept {
    return data[r][c];
  }

  constexpr Matrix4<Tp>& set(std::size_t r, std::size_t c, Tp value) noexcept {
    data[r][c] = value;
    return *this;
  }

  constexpr Vector3<Tp> MultiplyPoint(const Vector3<Tp>& p) const noexcept {
    Vector3<Tp> result{
        get(0, 0) * p.x + get(0, 1) * p.y + get(0, 2) * p.z + get(0, 3),
        get(1, 0) * p.x + get(1, 1) * p.y + get(1, 2) * p.z + get(1, 3),
        get(2, 0) * p.x + get(2, 1) * p.y + get(2, 2) * p.z + get(2, 3)};
    // auto w = get(3, 0) * p.x + get(3, 1) * p.y + get(3, 2) * p.z + get(3, 3);
    return result;
  }

  constexpr Vector3<Tp> MultiplyVector(const Vector3<Tp>& p) const noexcept {
    return Vector3<Tp>{get(0, 0) * p.x + get(0, 1) * p.y + get(0, 2) * p.z,
                       get(1, 0) * p.x + get(1, 1) * p.y + get(1, 2) * p.z,
                       get(2, 0) * p.x + get(2, 1) * p.y + get(2, 2) * p.z};
  }

  constexpr Matrix4<Tp> Transpose() const noexcept {
    Matrix4<Tp> result{};
    for (std::size_t r = 0; r < 4; ++r) {
      for (std::size_t c = 0; c < 4; ++c) {
        result[{r, c}] = get(c, r);
      }
    }
    return result;
  }

  std::string ToString() const noexcept {
    std::string str = "";
    for (std::size_t r = 0; r < 4; ++r) {
      str += "[ ";
      for (std::size_t c = 0; c < 4; ++c) {
        str += std::format("{:.2f} ", get(r, c));
      }
      str += "]\n";
    }
    return str;
  }
};

template <Numeric Tp>
constexpr Matrix4<Tp> operator*(const Matrix4<Tp>& a,
                                const Matrix4<Tp>& b) noexcept {
  Matrix4<Tp> result{};
  for (std::size_t r = 0; r < 4; ++r) {
    for (std::size_t c = 0; c < 4; ++c) {
      Tp s = 0;
      for (std::size_t x = 0; x < 4; ++x) {
        s += a[{r, x}] * b[{x, c}];
      }
      result[{r, c}] = s;
    }
  }
  return result;
}

}  // namespace rt
