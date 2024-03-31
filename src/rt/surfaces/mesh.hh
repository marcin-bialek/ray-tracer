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

  std::string ToString() const override;

 protected:
  std::optional<Intersection> DoHit(const Ray& ray) const override;

 private:
  std::vector<Triangle> triangles_;
};

}  // namespace rt
