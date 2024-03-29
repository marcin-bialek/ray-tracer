#pragma once

#include "material.hh"

namespace rt {

class MaterialSolid : public Material {
 public:
  explicit MaterialSolid() noexcept = default;

  const Vector3<>& color() const noexcept;

  MaterialSolid& SetColor(const Vector3<>& value) noexcept;

  Vector3<> GetColor(double u, double v) const override;
  std::string ToString() const override;

 private:
  Vector3<> color_;
};

}  // namespace rt
