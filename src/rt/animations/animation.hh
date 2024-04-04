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
  virtual ~Animation() noexcept = default;

  std::chrono::milliseconds duration() const noexcept {
    return duration_;
  }

  std::chrono::milliseconds delay() const noexcept {
    return delay_;
  }

  std::size_t iterations() const noexcept {
    return iterations_;
  }

  Direction direction() const noexcept {
    return direction_;
  }

  Animation<Tp>& SetDuration(std::chrono::milliseconds value) noexcept {
    duration_ = value;
    return *this;
  }

  Animation<Tp>& SetDelay(std::chrono::milliseconds value) noexcept {
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

  Animation<Tp>& SetTime(std::chrono::milliseconds time) noexcept {
    double t = 0.0;
    if (duration_ != std::chrono::milliseconds::zero() && time > delay_) {
      auto d = (time - delay_).count();
      auto n = d / duration_.count();
      if (iterations_ >= n) {
        t = static_cast<double>(d) / duration_.count() - n;
        if (direction_ == Direction::kReverse) {
          t = 1.0 - t;
        } else if (direction_ == Direction::kAlternate) {
          t = 1.0 - std::abs(2.0 * t - 1.0);
        } else if (direction_ == Direction::kAlternateReverse) {
          t = std::abs(2.0 * t - 1.0);
        }
      }
    }
    DoSetTime(t);
    return *this;
  }

  virtual const Tp& Get() const noexcept = 0;

  const Tp& operator*() const noexcept {
    return Get();
  }

  const Tp* operator->() const noexcept {
    return std::addressof(Get());
  }

 protected:
  std::chrono::milliseconds duration_{0};
  std::chrono::milliseconds delay_{0};
  std::size_t iterations_{0};
  Direction direction_{Direction::kForward};

  virtual void DoSetTime(double time) noexcept = 0;
};

}  // namespace rt
