#pragma once

#include <rt/common/color.hh>

#include "material.hh"

namespace rt {

class MaterialSolid : public Material {
 public:
  explicit MaterialSolid() noexcept = default;

  const Color& color() const noexcept;

  MaterialSolid& SetColor(const Color& value) noexcept;

  std::string ToString() const override;

 private:
  Color color_;
};

}  // namespace rt
