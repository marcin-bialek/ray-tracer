#include "material.hh"

namespace rt {

const Material::Phong& Material::phong() const noexcept {
  return phong_;
}

double Material::reflectance() const noexcept {
  return reflectance_;
}

double Material::transmittance() const noexcept {
  return transmittance_;
}

double Material::refraction() const noexcept {
  return refraction_;
}

Material& Material::SetPhong(double ka, double kd, double ks,
                             double exp) noexcept {
  phong_.ka = ka;
  phong_.kd = kd;
  phong_.ks = ks;
  phong_.exp = exp;
  return *this;
}

Material& Material::SetReflectance(double value) noexcept {
  reflectance_ = value;
  return *this;
}

Material& Material::SetTransmittance(double value) noexcept {
  transmittance_ = value;
  return *this;
}

Material& Material::SetRefraction(double value) noexcept {
  refraction_ = value;
  return *this;
}

}  // namespace rt
