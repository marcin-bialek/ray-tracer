#pragma once

#include <rt/material/material.hh>
#include <rt/math/vector3.hh>

namespace rt {

struct Intersection {
  const Material* material;
  Vector3<> point;
  Vector3<> normal;
  double distance;
  bool front;
  double u;
  double v;
};

}  // namespace rt
