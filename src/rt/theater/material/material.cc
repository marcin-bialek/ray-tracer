#include "material.hh"

namespace rt {

const Material::Phong& Material::phong() const noexcept {
  return phong_;
}

float Material::reflectance() const noexcept {
  return reflectance_;
}

float Material::transmittance() const noexcept {
  return transmittance_;
}

float Material::refraction() const noexcept {
  return refraction_;
}

Material& Material::SetPhong(float ka, float kd, float ks, float exp) noexcept {
  phong_.ka = ka;
  phong_.kd = kd;
  phong_.ks = ks;
  phong_.exp = exp;
  return *this;
}

Material& Material::SetReflectance(float value) noexcept {
  reflectance_ = value;
  return *this;
}

Material& Material::SetTransmittance(float value) noexcept {
  transmittance_ = value;
  return *this;
}

Material& Material::SetRefraction(float value) noexcept {
  refraction_ = value;
  return *this;
}

}  // namespace rt
