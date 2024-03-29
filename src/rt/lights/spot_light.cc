#include "spot_light.hh"

#include <rt/common/exception.hh>

namespace rt {

const Vector3<>& SpotLight::color() const noexcept {
  return color_;
}

const Vector3<>& SpotLight::position() const noexcept {
  return position_;
}

const Vector3<>& SpotLight::direction() const noexcept {
  return direction_;
}

const Angle<>& SpotLight::falloff_a1() const noexcept {
  return falloff_a1_;
}

const Angle<>& SpotLight::falloff_a2() const noexcept {
  return falloff_a2_;
}

SpotLight& SpotLight::SetColor(const Vector3<>& value) noexcept {
  color_ = value;
  return *this;
}

SpotLight& SpotLight::SetPosition(const Vector3<>& value) noexcept {
  position_ = value;
  return *this;
}

SpotLight& SpotLight::SetDirection(const Vector3<>& value) noexcept {
  direction_ = value;
  return *this;
}

SpotLight& SpotLight::SetFallof(const Angle<>& a1, const Angle<>& a2) noexcept {
  falloff_a1_ = a1;
  falloff_a2_ = a2;
  return *this;
}

double SpotLight::GetDistance(const Vector3<>& origin) const {
  throw RuntimeError{"not implemented"};
}

std::optional<Ray> SpotLight::GetShadowRay(const Vector3<>& origin) const {
  throw RuntimeError{"not implemented"};
}

Vector3<> SpotLight::Illuminate(const Ray& ray,
                                const Intersection& intersection) const {
  throw RuntimeError{"not implemented"};
}

std::string SpotLight::ToString() const {
  std::string str = "SpotLight\n";
  str += std::format("  color = {}\n", color_.ToString());
  str += std::format("  position = {}\n", position_.ToString());
  str += std::format("  direction = {}\n", direction_.ToString());
  str += std::format("  falloff = {}, {}\n", falloff_a1_.ToString(),
                     falloff_a2_.ToString());
  return str;
}

}  // namespace rt
