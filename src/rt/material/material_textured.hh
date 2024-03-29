#pragma once

#include <memory>

#include <rt/common/image.hh>

#include "material.hh"

namespace rt {

class MaterialTextured : public Material {
 public:
  explicit MaterialTextured() noexcept = default;

  const Image* image() const noexcept;

  MaterialTextured& SetImage(std::unique_ptr<Image> image) noexcept;

  Vector3<> GetColor(double u, double v) const override;
  std::string ToString() const override;

 private:
  std::unique_ptr<Image> image_;
};

}  // namespace rt
