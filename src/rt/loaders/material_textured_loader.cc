#include "material_textured_loader.hh"

#include <rt/common/exception.hh>

#include "common.hh"
#include "image_loader.hh"

namespace rt {

MaterialTexturedLoader::MaterialTexturedLoader(
    tinyxml2::XMLElement* element,
    const std::filesystem::path& directory) noexcept
    : element_{element}, directory_{directory} {}

std::unique_ptr<MaterialTextured> MaterialTexturedLoader::Load() {
  material_ = std::make_unique<MaterialTextured>();
  try {
    LoadTexture();
    LoadPhong();
    LoadReflectance();
    LoadTransmittance();
    LoadRefraction();
  } catch (std::exception& err) {
    throw RuntimeError{"error loading material textured: {}", err.what()};
  }
  return std::move(material_);
}

void MaterialTexturedLoader::LoadTexture() {
  auto elm_texture = element_->FirstChildElement("texture");
  if (elm_texture) {
    ImagerLoader loader{directory_ / elm_texture->Attribute("name")};
    material_->SetImage(loader.Load());
  } else {
    throw RuntimeError{"texture is not set"};
  }
}

void MaterialTexturedLoader::LoadPhong() {
  auto elm_phong = element_->FirstChildElement("phong");
  if (elm_phong) {
    auto ka = elm_phong->DoubleAttribute("ka");
    auto kd = elm_phong->DoubleAttribute("kd");
    auto ks = elm_phong->DoubleAttribute("ks");
    auto exp = elm_phong->DoubleAttribute("exponent");
    material_->SetPhong(ka, kd, ks, exp);
  } else {
    throw RuntimeError{"phong is not set"};
  }
}

void MaterialTexturedLoader::LoadReflectance() {
  auto elm_reflectance = element_->FirstChildElement("reflectance");
  if (elm_reflectance) {
    auto r = elm_reflectance->DoubleAttribute("r");
    material_->SetReflectance(r);
  } else {
    throw RuntimeError{"reflectance is not set"};
  }
}

void MaterialTexturedLoader::LoadTransmittance() {
  auto elm_transmittance = element_->FirstChildElement("transmittance");
  if (elm_transmittance) {
    auto t = elm_transmittance->DoubleAttribute("t");
    material_->SetTransmittance(t);
  } else {
    throw RuntimeError{"transmittance is not set"};
  }
}

void MaterialTexturedLoader::LoadRefraction() {
  auto elm_refraction = element_->FirstChildElement("refraction");
  if (elm_refraction) {
    auto iof = elm_refraction->DoubleAttribute("iof");
    material_->SetRefraction(iof);
  } else {
    throw RuntimeError{"refraction is not set"};
  }
}

}  // namespace rt
