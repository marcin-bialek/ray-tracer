#pragma once

#include <memory>

#include <tinyxml2/tinyxml2.hh>

#include <rt/theater/lights/parallel_light.hh>

namespace rt {

class ParallelLightLoader {
 public:
  explicit ParallelLightLoader(tinyxml2::XMLElement* element) noexcept;

  std::unique_ptr<ParallelLight> Load();

 private:
  tinyxml2::XMLElement* element_;
  std::unique_ptr<ParallelLight> light_;

  void LoadColor();
  void LoadDirection();
};

}  // namespace rt
