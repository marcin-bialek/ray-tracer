#pragma once

#include <memory>

#include <tinyxml2/tinyxml2.hh>

#include <rt/theater/camera.hh>

namespace rt {

class CameraLoader {
 public:
  explicit CameraLoader(tinyxml2::XMLElement* element) noexcept;

  std::unique_ptr<Camera> Load();

 private:
  tinyxml2::XMLElement* element_;
  std::unique_ptr<Camera> camera_;

  void LoadPosition();
  void LoadLookat();
  void LoadUp();
  void LoadHorizontalFov();
  void LoadResolution();
  void LoadMaxBounces();
};

}  // namespace rt
