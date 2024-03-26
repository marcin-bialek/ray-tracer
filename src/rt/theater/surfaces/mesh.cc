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

std::optional<Intersection> Mesh::Hit(const Ray& ray) const {
  static constexpr auto epsilon = std::numeric_limits<double>::epsilon();
  for (const auto& triangle : triangles_) {
    auto e1 = triangle.vertices[1] - triangle.vertices[0];
    auto e2 = triangle.vertices[2] - triangle.vertices[0];
    auto re2 = ray.direction.Cross(e2);
    auto det = e1.Dot(re2);
    if (-epsilon < det && det < epsilon) {
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
    if (t < epsilon) {
      continue;
    }
    Intersection inter{};
    inter.distance = t;
    inter.point = ray.At(t);
    inter.material = material_.get();
    inter.normal = (1 - u - v) * triangle.normals[0] + u * triangle.normals[1] +
                   v * triangle.normals[2];
    inter.front = ray.direction.Dot(inter.normal) < 0.0;
    if (!inter.front) {
      inter.normal = -inter.normal;
    }
    inter.u = (1 - u - v) * triangle.texture_coords[0].x +
              u * triangle.texture_coords[1].x +
              v * triangle.texture_coords[2].x;
    inter.v = (1 - u - v) * triangle.texture_coords[0].y +
              u * triangle.texture_coords[1].y +
              v * triangle.texture_coords[2].y;
    return inter;
  }
  return std::nullopt;
}

std::string Mesh::ToString() const {
  return "Mesh";
  // throw RuntimeError{"not implemented"};
}

}  // namespace rt
