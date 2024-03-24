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

std::optional<Intersection> Sphere::Hit(const Ray& ray) const {
  auto v = ray.origin - position_;
  auto a = ray.direction.Dot(ray.direction);
  auto b = 2.0 * v.Dot(ray.direction);
  auto c = v.Dot(v) - radius_ * radius_;
  auto d = b * b - 4 * a * c;
  if (d < 0.0) {
    return std::nullopt;
  }
  auto sd = std::sqrt(d);
  auto t0 = (-b - sd) / (2 * a);
  auto t1 = (-b + sd) / (2 * a);
  Intersection inter{};
  inter.material = material_.get();
  inter.distance = std::min(t0, t1);
  inter.point = ray.At(inter.distance);
  inter.normal = (inter.point - position_).Unit();
  inter.front = ray.direction.Dot(inter.normal) < 0.0;
  if (!inter.front) {
    inter.normal = -inter.normal;
  }
  return inter;
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
