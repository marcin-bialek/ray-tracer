#include "parallel_light.hh"

namespace rt {

const Color& ParallelLight::color() const noexcept {
  return color_;
}

const Vector3<>& ParallelLight::direction() const noexcept {
  return direction_;
}

ParallelLight& ParallelLight::SetColor(const Color& value) noexcept {
  color_ = value;
  return *this;
}

ParallelLight& ParallelLight::SetDirection(const Vector3<>& value) noexcept {
  direction_ = value;
  return *this;
}

std::string ParallelLight::ToString() const {
  std::string str = "ParallelLight\n";
  str += std::format("  color = {}\n", color_.ToString());
  str += std::format("  direction = {}\n", direction_.ToString());
  return str;
}

}  // namespace rt
