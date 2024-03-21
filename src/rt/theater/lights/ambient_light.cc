#include "ambient_light.hh"

#include <format>

namespace rt {

const Color& AmbientLight::color() const noexcept {
  return color_;
}

AmbientLight& AmbientLight::SetColor(const Color& value) noexcept {
  color_ = value;
  return *this;
}

std::string AmbientLight::ToString() const {
  std::string str = "AmbientLight\n";
  str += std::format("  color = {}\n", color_.ToString());
  return str;
}

}  // namespace rt
