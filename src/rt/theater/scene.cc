#include "scene.hh"

namespace rt {

Scene& Scene::SetCamera(std::unique_ptr<Camera> camera) noexcept {
  camera_ = std::move(camera);
  return *this;
}

Scene& Scene::AddLight(std::unique_ptr<Light> light) noexcept {
  lights_.push_back(std::move(light));
  return *this;
}

std::string Scene::ToString() const {
  std::string str = "Scene\n";
  str += camera_->ToString();
  for (auto& light : lights_) {
    str += light->ToString();
  }
  return str;
}

}  // namespace rt
