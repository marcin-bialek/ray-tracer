#pragma once

#include <memory>

#include <tinyxml2/tinyxml2.hh>

#include <rt/theater/lights/ambient_light.hh>

namespace rt {

class AmbientLightLoader {
 public:
  explicit AmbientLightLoader(tinyxml2::XMLElement* element) noexcept;

  std::unique_ptr<AmbientLight> Load();

 private:
  tinyxml2::XMLElement* element_;
  std::unique_ptr<AmbientLight> light_;

  void LoadColor();
};

}  // namespace rt
