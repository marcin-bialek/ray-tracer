#include "common.hh"

#include <string>

#include <rt/common/exception.hh>

namespace rt::details {

Vector3<> LoadVector3(tinyxml2::XMLElement* element) {
  auto attr_x = element->Attribute("x");
  if (!attr_x) {
    throw RuntimeError{"error parsing vector, no x coordinate"};
  }
  auto attr_y = element->Attribute("y");
  if (!attr_y) {
    throw RuntimeError{"error parsing vector, no y coordinate"};
  }
  auto attr_z = element->Attribute("z");
  if (!attr_z) {
    throw RuntimeError{"error parsing vector, no z coordinate"};
  }
  return {std::stod(attr_x), std::stod(attr_y), std::stod(attr_z)};
}

Vector3<> LoadColor(tinyxml2::XMLElement* element) {
  auto attr_r = element->Attribute("r");
  if (!attr_r) {
    throw RuntimeError{"error parsing color, no red value"};
  }
  auto attr_g = element->Attribute("g");
  if (!attr_g) {
    throw RuntimeError{"error parsing color, no green value"};
  }
  auto attr_b = element->Attribute("b");
  if (!attr_b) {
    throw RuntimeError{"error parsing color, no blue value"};
  }
  return {std::stod(attr_r), std::stod(attr_g), std::stod(attr_b)};
}

}  // namespace rt::details
