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

std::string Sphere::ToString() const {
  std::string str = "Sphere\n";
  str += std::format("  position = {}\n", position_.ToString());
  str += std::format("  radius = {}\n", radius_);
  if (material_) {
    str += material_->ToString();
  }
  return str;
}

std::optional<Intersection> Sphere::DoHit(const Ray& ray) const {
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
  if (t0 < 0.0 && t1 < 0.0) {
    return std::nullopt;
  } else if (t0 < 0.0 || t1 < 0.0) {
    inter.distance = std::max(t0, t1);
  } else {
    inter.distance = std::min(t0, t1);
  }
  inter.material = material_.get();
  inter.point = ray.At(inter.distance);
  inter.normal = (inter.point - position_).Unit();
  auto w = inter.point - position_;
  inter.u = 0.5 + std::atan2(w.x, w.z) / (2 * M_PI);
  inter.v = 0.5 - std::asin(w.y) / M_PI;
  return inter;
}

}  // namespace rt
