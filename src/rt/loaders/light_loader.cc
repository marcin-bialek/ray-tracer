#include "light_loader.hh"

#include <rt/common/exception.hh>
#include <rt/common/xml.hh>
#include <rt/theater/lights/ambient_light.hh>
#include <rt/theater/lights/parallel_light.hh>
#include <rt/theater/lights/point_light.hh>
#include <rt/theater/lights/spot_light.hh>

namespace rt {

LightLoader::LightLoader(tinyxml2::XMLElement* element) noexcept
    : element_{element} {}

LightLoader::LightPtr LightLoader::Load() {
  auto i = loaders_.find(element_->Name());
  if (i == loaders_.end()) {
    throw RuntimeError{"unsupported light {}", element_->Name()};
  }
  return (this->*(i->second))();
}

bool LightLoader::IsLight(tinyxml2::XMLElement* element) noexcept {
  return loaders_.contains(element->Name());
}

LightLoader::LightPtr LightLoader::LoadAmbientLight() {
  auto light = std::make_unique<AmbientLight>();
  try {
    light->SetColor(FirstGetAttrColor<>(element_, "color"));
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading ambient light, {}", err.what()};
  }
  return std::move(light);
}

LightLoader::LightPtr LightLoader::LoadParallelLight() {
  auto light = std::make_unique<ParallelLight>();
  try {
    light->SetColor(FirstGetAttrColor<>(element_, "color"));
    light->SetDirection(FirstGetAttrVector3<>(element_, "direction"));
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading parallel light, {}", err.what()};
  }
  return std::move(light);
}

LightLoader::LightPtr LightLoader::LoadPointLight() {
  auto light = std::make_unique<PointLight>();
  try {
    light->SetColor(FirstGetAttrColor<>(element_, "color"));
    light->SetPosition(FirstGetAttrVector3<>(element_, "position"));
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading point light, {}", err.what()};
  }
  return std::move(light);
}

LightLoader::LightPtr LightLoader::LoadSpotLight() {
  auto light = std::make_unique<SpotLight>();
  try {
    light->SetColor(FirstGetAttrColor<>(element_, "color"));
    light->SetPosition(FirstGetAttrVector3<>(element_, "position"));
    light->SetDirection(FirstGetAttrVector3<>(element_, "direction"));
    auto alpha1 = FirstGetAttrAngle<>(element_, "falloff", "alpha1");
    auto alpha2 = FirstGetAttrAngle<>(element_, "falloff", "alpha2");
    light->SetFallof(alpha1, alpha2);
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading spot light, {}", err.what()};
  }
  return std::move(light);
}

const std::map<std::string, LightLoader::LoaderPtr> LightLoader::loaders_{
    {"ambient_light", &LightLoader::LoadAmbientLight},
    {"parallel_light", &LightLoader::LoadParallelLight},
    {"point_light", &LightLoader::LoadPointLight},
    {"spot_light", &LightLoader::LoadSpotLight},
};

}  // namespace rt
