#pragma once

#include <rt/math/vector3.hh>
#include <rt/theater/material/material.hh>

namespace rt {

struct Intersection {
  const Material* material;
  Vector3<> point;
  Vector3<> normal;
  double distance;
  bool front;
};

}  // namespace rt
