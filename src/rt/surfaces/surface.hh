#pragma once

#include <optional>
#include <string>
#include <vector>

#include <rt/material/material.hh>
#include <rt/renderer/intersection.hh>
#include <rt/renderer/ray.hh>
#include <rt/transformations/transformation.hh>

namespace rt {

class Surface {
 public:
  virtual ~Surface() noexcept = default;

  const Material* material() const noexcept;

  Surface& SetMaterial(std::unique_ptr<Material> material) noexcept;
  Surface& AddTransformation(
      std::unique_ptr<Transformation> transformation) noexcept;

  virtual std::optional<Intersection> Hit(const Ray& ray) const = 0;
  virtual std::string ToString() const = 0;

 protected:
  std::unique_ptr<Material> material_;
  std::vector<std::unique_ptr<Transformation>> transformations_;
};

}  // namespace rt
