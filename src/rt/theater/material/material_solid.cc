#include "material_solid.hh"

#include <format>

namespace rt {

const Vector3<>& MaterialSolid::color() const noexcept {
  return color_;
}

MaterialSolid& MaterialSolid::SetColor(const Vector3<>& value) noexcept {
  color_ = value;
  return *this;
}

Vector3<> MaterialSolid::GetColor() const {
  return color_;
}

std::string MaterialSolid::ToString() const {
  std::string str = "MaterialSolid\n";
  str += std::format("  color = {}\n", color_.ToString());
  str += std::format("  phong = {}, {}, {}, {}\n", phong_.ka, phong_.kd,
                     phong_.ks, phong_.exp);
  str += std::format("  reflectance = {}\n", reflectance_);
  str += std::format("  transmittance = {}\n", transmittance_);
  str += std::format("  refraction = {}\n", refraction_);
  return str;
}

}  // namespace rt
