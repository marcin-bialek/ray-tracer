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

double Sphere::Intersection(const Ray& ray) const {
  auto op = ray.origin - position_;
  auto a = ray.direction.Dot(ray.direction);
  auto b = 2.0 * op.Dot(ray.direction);
  auto c = op.Dot(op) - radius_ * radius_;
  auto d = b * b - 4 * a * c;
  if (d < 0) {
    return -1.0;
  }
  auto sd = std::sqrt(d);
  auto t0 = (-b - sd) / (2 * a);
  auto t1 = (-b + sd) / (2 * a);
  return std::min(t0, t1);
}

Vector3<> Sphere::Normal(const Vector3<>& hit_point) const {
  return (hit_point - position_).Unit();
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
