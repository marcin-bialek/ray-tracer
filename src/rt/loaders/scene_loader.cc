#include "scene_loader.hh"

#include <rt/common/exception.hh>
#include <rt/common/xml.hh>

#include "light_loader.hh"
#include "surface_loader.hh"

namespace rt {

SceneLoader::SceneLoader(tinyxml2::XMLElement* element,
                         const std::filesystem::path& directory) noexcept
    : element_{element}, directory_{directory} {}

SceneLoader::ScenePtr SceneLoader::Load() {
  scene_ = std::make_unique<Scene>();
  try {
    LoadProperties();
    LoadCamera();
    LoadLights();
    LoadSurfaces();
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading scene, {}", err.what()};
  }
  return std::move(scene_);
}

void SceneLoader::LoadProperties() {
  scene_->SetBackground(FirstGetAttrColor(element_, "background_color"));
}

void SceneLoader::LoadCamera() {
  auto elm_camera = GetFirst(element_, "camera");
  auto camera = std::make_unique<Camera>();
  try {
    camera->SetPosition(FirstGetAttrVector3<>(elm_camera, "position"));
    camera->SetLookat(FirstGetAttrVector3<>(elm_camera, "lookat"));
    camera->SetUp(FirstGetAttrVector3<>(elm_camera, "up"));
    camera->SetHorizontalFov(
        FirstGetAttrAngle<>(elm_camera, "horizontal_fov", "angle"));
    camera->SetResolution(
        FirstGetAttr<std::size_t>(elm_camera, "resolution", "horizontal"),
        FirstGetAttr<std::size_t>(elm_camera, "resolution", "vertical"));
    camera->SetMaxBounces(
        FirstGetAttr<std::size_t>(elm_camera, "max_bounces", "n"));
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading camera, {}", err.what()};
  }
  scene_->SetCamera(std::move(camera));
}

void SceneLoader::LoadLights() {
  ForeachChild(GetFirst(element_, "lights"), [&](auto elm) {
    LightLoader light_loader{elm};
    scene_->AddLight(light_loader.Load());
  });
}

void SceneLoader::LoadSurfaces() {
  ForeachChild(GetFirst(element_, "surfaces"), [&](auto elm) {
    SurfaceLoader surface_loader{elm, directory_};
    scene_->AddSurface(surface_loader.Load());
  });
}

}  // namespace rt
