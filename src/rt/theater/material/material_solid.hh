#pragma once

#include "material.hh"

namespace rt {

class MaterialSolid : public Material {
 public:
  explicit MaterialSolid() noexcept = default;

  const Vector3<>& color() const noexcept;

  MaterialSolid& SetColor(const Vector3<>& value) noexcept;

  Vector3<> GetColor() const override;
  std::string ToString() const override;

 private:
  Vector3<> color_;
};

}  // namespace rt
