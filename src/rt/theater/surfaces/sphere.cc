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

}  // namespace rt
