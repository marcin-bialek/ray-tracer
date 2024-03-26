#include "ambient_light.hh"

#include <format>

namespace rt {

const Vector3<>& AmbientLight::color() const noexcept {
  return color_;
}

AmbientLight& AmbientLight::SetColor(const Vector3<>& value) noexcept {
  color_ = value;
  return *this;
}

std::optional<Ray> AmbientLight::GetShadowRay(const Vector3<>& origin) const {
  return std::nullopt;
}

Vector3<> AmbientLight::Illuminate(const Ray& ray,
                                   const Intersection& intersection) const {
  return (intersection.material->phong().ka *
          color_.Hadamard(intersection.material->GetColor()))
      .Clamp(0.0, 1.0);
}

std::string AmbientLight::ToString() const {
  std::string str = "AmbientLight\n";
  str += std::format("  color = {}\n", color_.ToString());
  return str;
}

}  // namespace rt
