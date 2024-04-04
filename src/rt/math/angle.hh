#pragma once

#include <cmath>
#include <format>

#include <rt/common/concepts.hh>

namespace rt {

template <Numeric Tp = double>
class Angle {
 public:
  constexpr Angle() noexcept = default;

  constexpr Angle(Tp degrees) noexcept {
    SetDegrees(degrees);
  }

  constexpr Tp degrees() const noexcept {
    return degrees_;
  }

  constexpr Tp radians() const noexcept {
    return radians_;
  }

  constexpr void SetDegrees(Tp value) noexcept {
    degrees_ = value;
    radians_ = value * M_PI / 180;
  }

  constexpr void SetRadians(Tp value) noexcept {
    degrees_ = value * 180 / M_PI;
    radians_ = value;
  }

  std::string ToString() const {
    return std::format("{} deg", degrees_);
  }

 private:
  Tp degrees_;
  Tp radians_;
};

template <Numeric Tp = double>
constexpr Angle<Tp> operator-(const Angle<Tp>& angle) noexcept {
  return -angle.degrees();
}

template <Numeric Tp = double>
constexpr Angle<Tp> operator+(const Angle<Tp>& a, const Angle<Tp>& b) noexcept {
  return a.degrees() + b.degrees();
}

template <Numeric Tp = double>
constexpr Angle<Tp> operator-(const Angle<Tp>& a, const Angle<Tp>& b) noexcept {
  return a.degrees() - b.degrees();
}

template <Numeric Tp = double>
constexpr Angle<Tp> operator*(const Angle<Tp>& a, const Angle<Tp>& b) noexcept {
  return a.degrees() * b.degrees();
}

template <Numeric Tp = double>
constexpr Angle<Tp> operator/(const Angle<Tp>& a, const Angle<Tp>& b) noexcept {
  return a.degrees() / b.degrees();
}

template <Numeric Tp = double>
constexpr Angle<Tp> operator*(double a, const Angle<Tp>& b) noexcept {
  return a * b.degrees();
}

template <Numeric Tp = double>
constexpr Angle<Tp> operator*(const Angle<Tp>& a, double b) noexcept {
  return a.degrees() * b;
}

}  // namespace rt
