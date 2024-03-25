#pragma once

#include <span>
#include <vector>

#include "surface.hh"
#include "triangle.hh"

namespace rt {

class Mesh : public Surface {
 public:
  explicit Mesh() noexcept = default;

  std::span<const Triangle> triangles() const noexcept;

  void SetTriangles(std::span<const Triangle> triangles) noexcept;
  void SetTriangles(std::vector<Triangle> triangles) noexcept;

  std::optional<Intersection> Hit(const Ray& ray) const override;
  std::string ToString() const override;

 private:
  std::vector<Triangle> triangles_;
};

}  // namespace rt
