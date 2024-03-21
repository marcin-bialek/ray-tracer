#include "point_light_loader.hh"

#include <rt/common/exception.hh>

#include "common.hh"

namespace rt {

PointLightLoader::PointLightLoader(tinyxml2::XMLElement* element) noexcept
    : element_{element} {}

std::unique_ptr<PointLight> PointLightLoader::Load() {
  light_ = std::make_unique<PointLight>();
  try {
    LoadColor();
    LoadPosition();
  } catch (std::exception& err) {
    throw RuntimeError{"error loading point light: {}", err.what()};
  }
  return std::move(light_);
}

void PointLightLoader::LoadColor() {
  auto elm_color = element_->FirstChildElement("color");
  if (elm_color) {
    light_->SetColor(details::LoadColor(elm_color));
  } else {
    throw RuntimeError{"color is not set"};
  }
}

void PointLightLoader::LoadPosition() {
  auto elm_position = element_->FirstChildElement("position");
  if (elm_position) {
    light_->SetPosition(details::LoadVector3(elm_position));
  } else {
    throw RuntimeError{"position is not set"};
  }
}

}  // namespace rt
