#include "sphere.hh"

#include <format>

namespace rt {

const Vector3<>& Sphere::position() const noexcept {
  return position_;
}

double Sphere::radius() const noexcept {
  return radius_;
}

Sphere& Sphere::SetPosition(const Vector3<>& value) noexcept {
  position_ = value;
  return *this;
}

Sphere& Sphere::SetRadius(double value) noexcept {
  radius_ = value;
  return *this;
}

bool Sphere::DoesHit(const Ray& ray) const {
  auto oc = ray.origin - position_;
  auto a = ray.direction.Dot(ray.direction);
  auto b = 2.0 * oc.Dot(ray.direction);
  auto c = oc.Dot(oc) - radius_ * radius_;
  auto disc = b * b - 4 * a * c;
  return disc >= 0;
}

std::string Sphere::ToString() const {
  std::string str = "Sphere\n";
  str += std::format("  position = {}\n", position_.ToString());
  str += std::format("  radius = {}\n", radius_);
  if (material_) {
    str += material_->ToString();
  }
  return str;
}

}  // namespace rt
