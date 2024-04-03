#include "scene.hh"

#include <format>

namespace rt {

const Vector3<>& Scene::background() const noexcept {
  return background_;
}

Camera& Scene::camera() noexcept {
  return *camera_;
}

const Camera& Scene::camera() const noexcept {
  return *camera_;
}

std::span<const std::unique_ptr<Surface>> Scene::surfaces() const noexcept {
  return surfaces_;
}

std::span<const std::unique_ptr<Light>> Scene::lights() const noexcept {
  return lights_;
}

Scene& Scene::SetBackground(const Vector3<>& color) noexcept {
  background_ = color;
  return *this;
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

Scene& Scene::SetTime(std::chrono::milliseconds time) noexcept {
  for (auto& surface : surfaces_) {
    surface->SetTime(time);
  }
  return *this;
}

std::string Scene::ToString() const {
  std::string str = "Scene\n";
  str += std::format("  background = {}\n", background_.ToString());
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
