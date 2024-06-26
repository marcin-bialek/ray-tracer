#pragma once

#include "animation.hh"

namespace rt {

template <Arithmetic Tp>
class LinearAnimation : public Animation<Tp> {
 public:
  explicit LinearAnimation(const Tp& begin, const Tp& end) noexcept
      : value_{begin}, begin_{begin}, end_{end} {}

  const Tp& Get() const noexcept override {
    return value_;
  }

 protected:
  void DoSetTime(double time) noexcept override {
    value_ = time * (end_ - begin_) + begin_;
  }

 private:
  Tp value_;
  Tp begin_;
  Tp end_;
};

}  // namespace rt
