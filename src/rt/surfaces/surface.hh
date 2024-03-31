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
  Surface& AddTransformation(const Transformation& transformation) noexcept;
  std::optional<Intersection> Hit(const Ray& ray) const;

  virtual std::string ToString() const = 0;

 protected:
  std::unique_ptr<Material> material_;

  virtual std::optional<Intersection> DoHit(const Ray& ray) const = 0;
};

}  // namespace rt
