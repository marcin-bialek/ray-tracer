#include "xml.hh"

namespace rt {

tinyxml2::XMLElement* GetFirst(tinyxml2::XMLElement* element,
                               std::string_view name) {
  auto e = element->FirstChildElement(name.data());
  if (!e) {
    throw RuntimeError{"no {}", name};
  }
  return e;
}

}  // namespace rt
