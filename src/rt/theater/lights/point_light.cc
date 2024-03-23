#include "point_light.hh"

namespace rt {

const Vector3<>& PointLight::color() const noexcept {
  return color_;
}

const Vector3<>& PointLight::position() const noexcept {
  return position_;
}

PointLight& PointLight::SetColor(const Vector3<>& value) noexcept {
  color_ = value;
  return *this;
}

PointLight& PointLight::SetPosition(const Vector3<>& value) noexcept {
  position_ = value;
  return *this;
}

std::string PointLight::ToString() const {
  std::string str = "PointLight\n";
  str += std::format("  color = {}\n", color_.ToString());
  str += std::format("  position = {}\n", position_.ToString());
  return str;
}

}  // namespace rt
