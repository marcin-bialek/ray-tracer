#include "material_solid_loader.hh"

#include <rt/common/exception.hh>

#include "common.hh"

namespace rt {

MaterialSolidLoader::MaterialSolidLoader(tinyxml2::XMLElement* element) noexcept
    : element_{element} {}

std::unique_ptr<MaterialSolid> MaterialSolidLoader::Load() {
  material_ = std::make_unique<MaterialSolid>();
  try {
    LoadColor();
    LoadPhong();
    LoadReflectance();
    LoadTransmittance();
    LoadRefraction();
  } catch (std::exception& err) {
    throw RuntimeError{"error loading material solid: {}", err.what()};
  }
  return std::move(material_);
}

void MaterialSolidLoader::LoadColor() {
  auto elm_color = element_->FirstChildElement("color");
  if (elm_color) {
    material_->SetColor(details::LoadColor(elm_color));
  } else {
    throw RuntimeError{"color is not set"};
  }
}

void MaterialSolidLoader::LoadPhong() {
  auto elm_phong = element_->FirstChildElement("phong");
  if (elm_phong) {
    auto ka = elm_phong->FloatAttribute("ka");
    auto kd = elm_phong->FloatAttribute("kd");
    auto ks = elm_phong->FloatAttribute("ks");
    auto exp = elm_phong->FloatAttribute("exponent");
    material_->SetPhong(ka, kd, ks, exp);
  } else {
    throw RuntimeError{"phong is not set"};
  }
}

void MaterialSolidLoader::LoadReflectance() {
  auto elm_reflectance = element_->FirstChildElement("reflectance");
  if (elm_reflectance) {
    auto r = elm_reflectance->FloatAttribute("r");
    material_->SetReflectance(r);
  } else {
    throw RuntimeError{"reflectance is not set"};
  }
}

void MaterialSolidLoader::LoadTransmittance() {
  auto elm_transmittance = element_->FirstChildElement("transmittance");
  if (elm_transmittance) {
    auto t = elm_transmittance->FloatAttribute("t");
    material_->SetTransmittance(t);
  } else {
    throw RuntimeError{"transmittance is not set"};
  }
}

void MaterialSolidLoader::LoadRefraction() {
  auto elm_refraction = element_->FirstChildElement("refraction");
  if (elm_refraction) {
    auto iof = elm_refraction->FloatAttribute("iof");
    material_->SetRefraction(iof);
  } else {
    throw RuntimeError{"refraction is not set"};
  }
}

}  // namespace rt
