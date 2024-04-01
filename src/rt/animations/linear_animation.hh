#pragma once

#include "animation.hh"

namespace rt {

template <Arithmetic Tp>
class LinearAnimation : public Animation<Tp> {
 public:
  explicit LinearAnimation(const Tp& begin, const Tp& end) noexcept
      : begin_{begin}, end_{end} {}

 private:
  Tp begin_;
  Tp end_;

  Tp DoGet(double t) const noexcept override {
    return t * (end_ - begin_) + begin_;
  }
};

}  // namespace rt
