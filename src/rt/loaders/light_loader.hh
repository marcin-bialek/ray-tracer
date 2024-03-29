#pragma once

#include <map>
#include <memory>
#include <string>

#include <tinyxml2/tinyxml2.hh>

#include <rt/theater/lights/light.hh>

namespace rt {

class LightLoader {
 public:
  using LightPtr = std::unique_ptr<Light>;

  explicit LightLoader(tinyxml2::XMLElement* element) noexcept;

  LightPtr Load();

  static bool IsLight(tinyxml2::XMLElement* element) noexcept;

 private:
  tinyxml2::XMLElement* element_;

  LightPtr LoadAmbientLight();
  LightPtr LoadParallelLight();
  LightPtr LoadPointLight();
  LightPtr LoadSpotLight();

  using LoaderPtr = LightPtr (LightLoader::*)();
  static const std::map<std::string, LoaderPtr> loaders_;
};

}  // namespace rt
