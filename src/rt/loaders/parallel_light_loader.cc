#include "parallel_light_loader.hh"

#include <rt/common/exception.hh>

#include "common.hh"

namespace rt {

ParallelLightLoader::ParallelLightLoader(tinyxml2::XMLElement* element) noexcept
    : element_{element} {}

std::unique_ptr<ParallelLight> ParallelLightLoader::Load() {
  light_ = std::make_unique<ParallelLight>();
  try {
    LoadColor();
    LoadDirection();
  } catch (std::exception& err) {
    throw RuntimeError{"error loading parallel light: {}", err.what()};
  }
  return std::move(light_);
}

void ParallelLightLoader::LoadColor() {
  auto elm_color = element_->FirstChildElement("color");
  if (elm_color) {
    light_->SetColor(details::LoadColor(elm_color));
  } else {
    throw RuntimeError{"color is not set"};
  }
}

void ParallelLightLoader::LoadDirection() {
  auto elm_direction = element_->FirstChildElement("direction");
  if (elm_direction) {
    light_->SetDirection(details::LoadVector3(elm_direction));
  } else {
    throw RuntimeError{"direction is not set"};
  }
}

}  // namespace rt
