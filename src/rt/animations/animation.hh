#pragma once

#include <chrono>

#include <rt/common/concepts.hh>

namespace rt {

enum class Direction {
  kForward,
  kReverse,
  kAlternate,
  kAlternateReverse,
};

template <Arithmetic Tp>
class Animation {
 public:
  static constexpr auto kInfinite = std::numeric_limits<std::size_t>::max();

  virtual ~Animation() noexcept = default;

  const std::chrono::milliseconds& duration() const noexcept {
    return duration_;
  }

  const std::chrono::milliseconds& delay() const noexcept {
    return delay_;
  }

  std::size_t iterations() const noexcept {
    return iterations_;
  }

  Direction direction() const noexcept {
    return direction_;
  }

  Animation<Tp>& SetDuration(const std::chrono::milliseconds& value) noexcept {
    duration_ = value;
    return *this;
  }

  Animation<Tp>& SetDelay(const std::chrono::milliseconds& value) noexcept {
    delay_ = value;
    return *this;
  }

  Animation<Tp>& SetIterations(std::size_t value) noexcept {
    iterations_ = value;
    return *this;
  }

  Animation<Tp>& SetDirection(Direction value) noexcept {
    direction_ = value;
    return *this;
  }

  Tp Get(const std::chrono::milliseconds& time) const noexcept {
    if (duration_ == std::chrono::milliseconds::zero() || time < delay_) {
      return DoGet(0);
    }
    auto d = (time - delay_).count();
    auto n = d / duration_.count();
    if (iterations_ < n) {
      return DoGet(0);
    }
    auto t = static_cast<double>(d) / static_cast<double>(duration_.count()) -
             static_cast<double>(n);
    return DoGet(t);
  }

 protected:
  std::chrono::milliseconds duration_;
  std::chrono::milliseconds delay_;
  std::size_t iterations_;
  Direction direction_;

  virtual Tp DoGet(double t) const noexcept = 0;
};

}  // namespace rt
