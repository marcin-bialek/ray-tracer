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

}  // namespace rt
