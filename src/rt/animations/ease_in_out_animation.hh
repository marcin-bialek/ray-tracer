#pragma once

#include "animation.hh"

namespace rt {

template <Arithmetic Tp>
class EaseInOutAnimation : public Animation<Tp> {
 public:
  explicit EaseInOutAnimation(const Tp& begin, const Tp& end) noexcept
      : value_{begin}, begin_{begin}, end_{end} {}

  const Tp& Get() const noexcept override {
    return value_;
  }

 protected:
  void DoSetTime(double time) noexcept override {
    double t = 0.0;
    if (time < 0.5) {
      t = 2.0 * std::pow(time, 2);
    } else {
      t = 2.0 * time * (1.0 - time) + 0.5;
    }
    value_ = t * (end_ - begin_) + begin_;
  }

 private:
  Tp value_;
  Tp begin_;
  Tp end_;
};

}  // namespace rt
