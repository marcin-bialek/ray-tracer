#pragma once

#include <string>

#include <rt/math/vector3.hh>

namespace rt {

class Material {
 public:
  struct Phong {
    double ka;
    double kd;
    double ks;
    double exp;
  };

  virtual ~Material() noexcept = default;

  const Phong& phong() const noexcept;
  double reflectance() const noexcept;
  double transmittance() const noexcept;
  double refraction() const noexcept;

  Material& SetPhong(double ka, double kd, double ks, double exp) noexcept;
  Material& SetReflectance(double value) noexcept;
  Material& SetTransmittance(double value) noexcept;
  Material& SetRefraction(double value) noexcept;

  virtual Vector3<> GetColor(double u, double v) const = 0;
  virtual std::string ToString() const = 0;

 protected:
  Phong phong_;
  double reflectance_;
  double transmittance_;
  double refraction_;
};

}  // namespace rt
