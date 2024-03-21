#include "ambient_light_loader.hh"

#include <rt/common/exception.hh>

#include "common.hh"

namespace rt {

AmbientLightLoader::AmbientLightLoader(tinyxml2::XMLElement* element) noexcept
    : element_{element} {}

std::unique_ptr<AmbientLight> AmbientLightLoader::Load() {
  light_ = std::make_unique<AmbientLight>();
  try {
    LoadColor();
  } catch (std::exception& err) {
    throw RuntimeError{"error loading ambient light: {}", err.what()};
  }
  return std::move(light_);
}

void AmbientLightLoader::LoadColor() {
  auto elm_color = element_->FirstChildElement("color");
  if (elm_color) {
    light_->SetColor(details::LoadColor(elm_color));
  } else {
    throw RuntimeError{"color is not set"};
  }
}

}  // namespace rt
