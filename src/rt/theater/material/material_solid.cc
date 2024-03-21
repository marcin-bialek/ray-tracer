#include "material_solid.hh"

#include <format>

namespace rt {

const Color& MaterialSolid::color() const noexcept {
  return color_;
}

MaterialSolid& MaterialSolid::SetColor(const Color& value) noexcept {
  color_ = value;
  return *this;
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
