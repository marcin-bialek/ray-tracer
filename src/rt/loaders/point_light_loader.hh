#pragma once

#include <memory>

#include <tinyxml2/tinyxml2.hh>

#include <rt/theater/lights/point_light.hh>

namespace rt {

class PointLightLoader {
 public:
  explicit PointLightLoader(tinyxml2::XMLElement* element) noexcept;

  std::unique_ptr<PointLight> Load();

 private:
  tinyxml2::XMLElement* element_;
  std::unique_ptr<PointLight> light_;

  void LoadColor();
  void LoadPosition();
};

}  // namespace rt
