#include "parallel_light.hh"

#include <cmath>

#include <rt/common/exception.hh>

namespace rt {

const Vector3<>& ParallelLight::color() const noexcept {
  return color_;
}

const Vector3<>& ParallelLight::direction() const noexcept {
  return direction_;
}

ParallelLight& ParallelLight::SetColor(const Vector3<>& value) noexcept {
  color_ = value;
  return *this;
}

ParallelLight& ParallelLight::SetDirection(const Vector3<>& value) noexcept {
  direction_ = value.Unit();
  return *this;
}

double ParallelLight::GetDistance(const Vector3<>& origin) const {
  return std::numeric_limits<double>::infinity();
}

std::optional<Ray> ParallelLight::GetShadowRay(const Vector3<>& origin) const {
  return Ray{origin, -direction_};
}

Vector3<> ParallelLight::Illuminate(const Ray& ray,
                                    const Intersection& intersection) const {
  auto& phong = intersection.material->phong();
  auto L = -direction_;
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

std::string ParallelLight::ToString() const {
  std::string str = "ParallelLight\n";
  str += std::format("  color = {}\n", color_.ToString());
  str += std::format("  direction = {}\n", direction_.ToString());
  return str;
}

}  // namespace rt
