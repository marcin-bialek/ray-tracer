#pragma once

#include <memory>

#include <tinyxml2/tinyxml2.hh>

#include <rt/theater/scene.hh>

namespace rt {

class SceneLoader {
 public:
  explicit SceneLoader(tinyxml2::XMLDocument* document) noexcept;

  std::unique_ptr<Scene> Load();

 private:
  tinyxml2::XMLDocument* document_;
  std::unique_ptr<Scene> scene_;

  void LoadCamera(tinyxml2::XMLElement* element);
  void LoadLights(tinyxml2::XMLElement* element);
  void LoadSurfaces(tinyxml2::XMLElement* element);
};

}  // namespace rt
