#include "scene_loader.hh"

#include <iostream>

#include <rt/common/exception.hh>

#include "ambient_light_loader.hh"
#include "camera_loader.hh"
#include "parallel_light_loader.hh"
#include "point_light_loader.hh"
#include "spot_light_loader.hh"

namespace rt {

SceneLoader::SceneLoader(tinyxml2::XMLDocument* document) noexcept
    : document_{document} {}

std::unique_ptr<Scene> SceneLoader::Load() {
  scene_ = std::make_unique<Scene>();
  auto elm_scene = document_->FirstChildElement();
  LoadCamera(elm_scene->FirstChildElement("camera"));
  LoadLights(elm_scene->FirstChildElement("lights"));
  return std::move(scene_);
}

void SceneLoader::LoadCamera(tinyxml2::XMLElement* element) {
  if (!element) {
    throw RuntimeError{"error loading scene: no camera"};
  }
  CameraLoader loader{element};
  scene_->SetCamera(loader.Load());
}

void SceneLoader::LoadLights(tinyxml2::XMLElement* element) {
  auto elm = element->FirstChildElement();
  while (elm) {
    auto name = std::string_view{elm->Name()};
    if (name == "ambient_light") {
      AmbientLightLoader loader{elm};
      scene_->AddLight(loader.Load());
    } else if (name == "parallel_light") {
      ParallelLightLoader loader{elm};
      scene_->AddLight(loader.Load());
    } else if (name == "point_light") {
      PointLightLoader loader{elm};
      scene_->AddLight(loader.Load());
    } else if (name == "spot_light") {
      SpotLightLoader loader{elm};
      scene_->AddLight(loader.Load());
    } else {
      std::cerr << std::format("Warning: unknown light type {}, skipped", name)
                << std::endl;
    }
    elm = elm->NextSiblingElement();
  }
}

}  // namespace rt
