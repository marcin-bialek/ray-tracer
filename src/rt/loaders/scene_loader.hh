#pragma once

#include <filesystem>
#include <memory>

#include <tinyxml2/tinyxml2.hh>

#include <rt/scene/scene.hh>

namespace rt {

class SceneLoader {
 public:
  using ScenePtr = std::unique_ptr<Scene>;

  explicit SceneLoader(tinyxml2::XMLElement* element,
                       const std::filesystem::path& directory) noexcept;

  ScenePtr Load();

 private:
  tinyxml2::XMLElement* element_;
  std::filesystem::path directory_;
  ScenePtr scene_;

  void LoadProperties();
  void LoadCamera();
  void LoadLights();
  void LoadSurfaces();
};

}  // namespace rt
