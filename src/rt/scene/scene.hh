#pragma once

#include <chrono>
#include <memory>
#include <span>
#include <string>
#include <vector>

#include <rt/lights/light.hh>
#include <rt/surfaces/surface.hh>

#include "camera.hh"

namespace rt {

class Scene {
 public:
  explicit Scene() noexcept = default;

  const Vector3<>& background() const noexcept;
  Camera& camera() noexcept;
  const Camera& camera() const noexcept;
  std::span<const std::unique_ptr<Surface>> surfaces() const noexcept;
  std::span<const std::unique_ptr<Light>> lights() const noexcept;

  Scene& SetBackground(const Vector3<>& color) noexcept;
  Scene& SetCamera(std::unique_ptr<Camera> camera) noexcept;
  Scene& AddLight(std::unique_ptr<Light> light) noexcept;
  Scene& AddSurface(std::unique_ptr<Surface> surface) noexcept;
  Scene& SetTime(std::chrono::milliseconds time) noexcept;

  std::string ToString() const;

 private:
  Vector3<> background_;
  std::unique_ptr<Camera> camera_;
  std::vector<std::unique_ptr<Light>> lights_;
  std::vector<std::unique_ptr<Surface>> surfaces_;
};

}  // namespace rt
