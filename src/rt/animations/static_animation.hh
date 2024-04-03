#pragma once

#include "animation.hh"

namespace rt {

template <Arithmetic Tp>
class StaticAnimation : public Animation<Tp> {
 public:
  explicit StaticAnimation(const Tp& value) noexcept : value_{value} {}

  const Tp& Get() const noexcept override {
    return value_;
  }

 protected:
  void DoSetTime(double time) noexcept override {}

 private:
  Tp value_;
};

}  // namespace rt
