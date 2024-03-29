#include "point_light.hh"

#include <rt/common/exception.hh>

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

double PointLight::GetDistance(const Vector3<>& origin) const {
  return (position_ - origin).Length();
}

std::optional<Ray> PointLight::GetShadowRay(const Vector3<>& origin) const {
  return Ray{origin, (position_ - origin).Unit()};
}

Vector3<> PointLight::Illuminate(const Ray& ray,
                                 const Intersection& intersection) const {
  auto& phong = intersection.material->phong();
  auto L = (position_ - intersection.point).Unit();
  auto V = -ray.direction;
  auto LN = L.Dot(intersection.normal);
  auto R = 2 * LN * intersection.normal - L;
  auto d = std::max(0.0, phong.kd * LN);
  auto s = phong.ks * std::pow(std::max(0.0, R.Dot(V)), phong.exp);
  return (d * color_.Hadamard(intersection.material->GetColor(intersection.u,
                                                              intersection.v)) +
          s * color_)
      .Clamp(0.0, 1.0);
}

std::string PointLight::ToString() const {
  std::string str = "PointLight\n";
  str += std::format("  color = {}\n", color_.ToString());
  str += std::format("  position = {}\n", position_.ToString());
  return str;
}

}  // namespace rt
