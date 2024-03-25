#pragma once

#include <filesystem>
#include <memory>

#include <tinyxml2/tinyxml2.hh>

#include <rt/theater/scene.hh>

namespace rt {

class SceneLoader {
 public:
  explicit SceneLoader(tinyxml2::XMLDocument* document,
                       const std::filesystem::path& directory) noexcept;

  std::unique_ptr<Scene> Load();

 private:
  tinyxml2::XMLDocument* document_;
  std::filesystem::path directory_;
  std::unique_ptr<Scene> scene_;

  void LoadBackground(tinyxml2::XMLElement* element);
  void LoadCamera(tinyxml2::XMLElement* element);
  void LoadLights(tinyxml2::XMLElement* element);
  void LoadSurfaces(tinyxml2::XMLElement* element);
};

}  // namespace rt
