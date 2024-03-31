#include "mesh.hh"

#include <rt/common/exception.hh>

namespace rt {

std::span<const Triangle> Mesh::triangles() const noexcept {
  return triangles_;
}

void Mesh::SetTriangles(std::span<const Triangle> triangles) noexcept {
  SetTriangles(std::vector<Triangle>{triangles.begin(), triangles.end()});
}

void Mesh::SetTriangles(std::vector<Triangle> triangles) noexcept {
  triangles_ = std::move(triangles);
}

std::string Mesh::ToString() const {
  std::string str = "Mesh\n";
  if (material_) {
    str += material_->ToString();
  }
  return str;
}

std::optional<Intersection> Mesh::DoHit(const Ray& ray) const {
  static constexpr auto kEpsilon = 0.00001;
  const Triangle* min_triangle = nullptr;
  auto min_t = std::numeric_limits<double>::infinity();
  auto min_u = 0.0;
  auto min_v = 0.0;
  for (const auto& triangle : triangles_) {
    auto e1 = triangle.vertices[1] - triangle.vertices[0];
    auto e2 = triangle.vertices[2] - triangle.vertices[0];
    auto re2 = ray.direction.Cross(e2);
    auto det = e1.Dot(re2);
    if (-kEpsilon < det && det < kEpsilon) {
      continue;
    }
    auto s = ray.origin - triangle.vertices[0];
    auto u = s.Dot(re2) / det;
    if (u < 0 || 1 < u) {
      continue;
    }
    auto se1 = s.Cross(e1);
    auto v = ray.direction.Dot(se1) / det;
    if (v < 0 || 1 < u + v) {
      continue;
    }
    auto t = e2.Dot(se1) / det;
    if (kEpsilon < t && t < min_t) {
      min_triangle = &triangle;
      min_t = t;
      min_u = u;
      min_v = v;
    }
  }
  if (!min_triangle) {
    return std::nullopt;
  }
  Intersection inter{};
  inter.distance = min_t;
  inter.point = ray.At(min_t);
  inter.material = material_.get();
  inter.normal = (1 - min_u - min_v) * min_triangle->normals[0] +
                 min_u * min_triangle->normals[1] +
                 min_v * min_triangle->normals[2];
  inter.u = (1 - min_u - min_v) * min_triangle->texture_coords[0].x +
            min_u * min_triangle->texture_coords[1].x +
            min_v * min_triangle->texture_coords[2].x;
  inter.v = (1 - min_u - min_v) * min_triangle->texture_coords[0].y +
            min_u * min_triangle->texture_coords[1].y +
            min_v * min_triangle->texture_coords[2].y;
  return inter;
}

}  // namespace rt
