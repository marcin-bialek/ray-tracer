#pragma once

#include <tinyxml2/tinyxml2.hh>

#include <rt/common/color.hh>
#include <rt/math/vector3.hh>

namespace rt::details {

Vector3<> LoadVector3(tinyxml2::XMLElement* element);
Color LoadColor(tinyxml2::XMLElement* element);

}  // namespace rt::details
