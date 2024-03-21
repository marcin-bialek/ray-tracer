#include "color.hh"

#include <format>

namespace rt {

std::string Color::ToString() const {
  return std::format("RGB{{{}, {}, {}}}", r, g, b);
}

}  // namespace rt
