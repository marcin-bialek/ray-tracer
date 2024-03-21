#pragma once

#include <algorithm>
#include <cinttypes>
#include <concepts>
#include <string>

namespace rt {

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;

  constexpr Color() noexcept = default;

  constexpr Color(uint8_t r, uint8_t g, uint8_t b) noexcept
      : r{r}, g{g}, b{b} {}

  template <std::floating_point Tp>
  constexpr Color(Tp r, Tp g, Tp b) noexcept
      : r{static_cast<uint8_t>(std::clamp<Tp>(r, 0, 1) * 255)},
        g{static_cast<uint8_t>(std::clamp<Tp>(g, 0, 1) * 255)},
        b{static_cast<uint8_t>(std::clamp<Tp>(b, 0, 1) * 255)} {}

  std::string ToString() const;
};

constexpr Color operator+(const Color& a, const Color& b) noexcept {
  return {
      static_cast<uint8_t>(
          std::clamp(static_cast<int>(a.r) + static_cast<int>(b.r), 0, 255)),
      static_cast<uint8_t>(
          std::clamp(static_cast<int>(a.g) + static_cast<int>(b.g), 0, 255)),
      static_cast<uint8_t>(
          std::clamp(static_cast<int>(a.b) + static_cast<int>(b.b), 0, 255)),
  };
}

template <std::floating_point Tp>
constexpr Color operator*(Tp s, const Color& color) noexcept {
  return {
      static_cast<uint8_t>(std::clamp<Tp>(s * color.r, 0, 255)),
      static_cast<uint8_t>(std::clamp<Tp>(s * color.g, 0, 255)),
      static_cast<uint8_t>(std::clamp<Tp>(s * color.b, 0, 255)),
  };
}

template <std::floating_point Tp>
constexpr Color operator*(const Color& color, Tp s) noexcept {
  return s * color;
}

template <std::floating_point Tp>
constexpr Color operator/(const Color& color, Tp s) noexcept {
  return {
      static_cast<uint8_t>(std::clamp<Tp>(color.r / s, 0, 255)),
      static_cast<uint8_t>(std::clamp<Tp>(color.g / s, 0, 255)),
      static_cast<uint8_t>(std::clamp<Tp>(color.b / s, 0, 255)),
  };
}

}  // namespace rt
