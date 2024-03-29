#pragma once

#include <array>

#include <rt/math/vector3.hh>

namespace rt {

struct Triangle {
  std::array<Vector3<>, 3> vertices;
  std::array<Vector3<>, 3> normals;
  std::array<Vector3<>, 3> texture_coords;
};

}  // namespace rt
