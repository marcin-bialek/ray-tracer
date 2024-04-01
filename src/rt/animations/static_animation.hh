#pragma once

#include "animation.hh"

namespace rt {

template <Arithmetic Tp>
class StaticAnimation : public Animation<Tp> {
 public:
  explicit StaticAnimation(const Tp& value) noexcept : value_{value} {}

 private:
  Tp value_;

  Tp DoGet(double t) const noexcept override {
    return value_;
  }
};

}  // namespace rt
