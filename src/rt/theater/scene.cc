#include "scene.hh"

namespace rt {

Camera* Scene::camera() noexcept {
  return camera_.get();
}

const Camera* Scene::camera() const noexcept {
  return camera_.get();
}

Scene& Scene::SetCamera(std::unique_ptr<Camera> camera) noexcept {
  camera_ = std::move(camera);
  return *this;
}

Scene& Scene::AddLight(std::unique_ptr<Light> light) noexcept {
  lights_.push_back(std::move(light));
  return *this;
}

Scene& Scene::AddSurface(std::unique_ptr<Surface> surface) noexcept {
  surfaces_.push_back(std::move(surface));
  return *this;
}

std::string Scene::ToString() const {
  std::string str = "Scene\n";
  str += camera_->ToString();
  for (auto& light : lights_) {
    str += light->ToString();
  }
  for (auto& surface : surfaces_) {
    str += surface->ToString();
  }
  return str;
}

}  // namespace rt
