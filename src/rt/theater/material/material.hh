#pragma once

#include <string>

namespace rt {

class Material {
 public:
  struct Phong {
    float ka;
    float kd;
    float ks;
    float exp;
  };

  virtual ~Material() noexcept = default;

  const Phong& phong() const noexcept;
  float reflectance() const noexcept;
  float transmittance() const noexcept;
  float refraction() const noexcept;

  Material& SetPhong(float ka, float kd, float ks, float exp) noexcept;
  Material& SetReflectance(float value) noexcept;
  Material& SetTransmittance(float value) noexcept;
  Material& SetRefraction(float value) noexcept;

  virtual std::string ToString() const = 0;

 protected:
  Phong phong_;
  float reflectance_;
  float transmittance_;
  float refraction_;
};

}  // namespace rt
