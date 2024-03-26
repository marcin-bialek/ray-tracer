#include "scene_loader.hh"

#include <iostream>

#include <rt/common/exception.hh>

#include "ambient_light_loader.hh"
#include "camera_loader.hh"
#include "common.hh"
#include "mesh_loader.hh"
#include "parallel_light_loader.hh"
#include "point_light_loader.hh"
#include "sphere_loader.hh"
#include "spot_light_loader.hh"

namespace rt {

SceneLoader::SceneLoader(tinyxml2::XMLDocument* document,
                         const std::filesystem::path& directory) noexcept
    : document_{document}, directory_{directory} {}

std::unique_ptr<Scene> SceneLoader::Load() {
  scene_ = std::make_unique<Scene>();
  auto elm_scene = document_->FirstChildElement();
  LoadBackground(elm_scene->FirstChildElement("background_color"));
  LoadCamera(elm_scene->FirstChildElement("camera"));
  LoadLights(elm_scene->FirstChildElement("lights"));
  LoadSurfaces(elm_scene->FirstChildElement("surfaces"));
  return std::move(scene_);
}

void SceneLoader::LoadBackground(tinyxml2::XMLElement* element) {
  if (!element) {
    throw RuntimeError{"error loading scene: no background color"};
  }
  scene_->SetBackground(details::LoadColor(element));
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

void SceneLoader::LoadSurfaces(tinyxml2::XMLElement* element) {
  auto elm = element->FirstChildElement();
  while (elm) {
    auto name = std::string_view{elm->Name()};
    if (name == "sphere") {
      SphereLoader loader{elm, directory_};
      scene_->AddSurface(loader.Load());
    } else if (name == "mesh") {
      MeshLoader loader{elm, directory_};
      scene_->AddSurface(loader.Load());
    } else {
      std::cerr << std::format("Warning: unknown surface type {}, skipped",
                               name)
                << std::endl;
    }
    elm = elm->NextSiblingElement();
  }
}

}  // namespace rt
