#include "spot_light_loader.hh"

#include <rt/common/exception.hh>

#include "common.hh"

namespace rt {

SpotLightLoader::SpotLightLoader(tinyxml2::XMLElement* element) noexcept
    : element_{element} {}

std::unique_ptr<SpotLight> SpotLightLoader::Load() {
  light_ = std::make_unique<SpotLight>();
  try {
    LoadColor();
    LoadPosition();
    LoadDirection();
    LoadFalloff();
  } catch (std::exception& err) {
    throw RuntimeError{"error loading spot light: {}", err.what()};
  }
  return std::move(light_);
}

void SpotLightLoader::LoadColor() {
  auto elm_color = element_->FirstChildElement("color");
  if (elm_color) {
    light_->SetColor(details::LoadColor(elm_color));
  } else {
    throw RuntimeError{"color is not set"};
  }
}

void SpotLightLoader::LoadPosition() {
  auto elm_position = element_->FirstChildElement("position");
  if (elm_position) {
    light_->SetPosition(details::LoadVector3(elm_position));
  } else {
    throw RuntimeError{"position is not set"};
  }
}

void SpotLightLoader::LoadDirection() {
  auto elm_direction = element_->FirstChildElement("direction");
  if (elm_direction) {
    light_->SetDirection(details::LoadVector3(elm_direction));
  } else {
    throw RuntimeError{"direction is not set"};
  }
}

void SpotLightLoader::LoadFalloff() {
  auto elm_falloff = element_->FirstChildElement("falloff");
  if (elm_falloff) {
    auto a1 = Angle{elm_falloff->DoubleAttribute("alpha1")};
    auto a2 = Angle{elm_falloff->DoubleAttribute("alpha2")};
    light_->SetFallof(a1, a2);
  } else {
    throw RuntimeError{"falloff is not set"};
  }
}

}  // namespace rt
