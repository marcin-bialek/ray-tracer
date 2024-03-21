#pragma once

#include <memory>

#include <tinyxml2/tinyxml2.hh>

#include <rt/theater/lights/spot_light.hh>

namespace rt {

class SpotLightLoader {
 public:
  explicit SpotLightLoader(tinyxml2::XMLElement* element) noexcept;

  std::unique_ptr<SpotLight> Load();

 private:
  tinyxml2::XMLElement* element_;
  std::unique_ptr<SpotLight> light_;

  void LoadColor();
  void LoadPosition();
  void LoadDirection();
  void LoadFalloff();
};

}  // namespace rt
