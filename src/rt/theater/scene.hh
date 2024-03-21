#pragma once

#include <memory>
#include <string>
#include <vector>

#include "camera.hh"
#include "lights/light.hh"
#include "surfaces/surface.hh"

namespace rt {

class Scene {
 public:
  explicit Scene() noexcept = default;

  Camera* camera() noexcept;
  const Camera* camera() const noexcept;

  Scene& SetCamera(std::unique_ptr<Camera> camera) noexcept;
  Scene& AddLight(std::unique_ptr<Light> light) noexcept;
  Scene& AddSurface(std::unique_ptr<Surface> surface) noexcept;

  std::string ToString() const;

 private:
  std::unique_ptr<Camera> camera_;
  std::vector<std::unique_ptr<Light>> lights_;
  std::vector<std::unique_ptr<Surface>> surfaces_;
};

}  // namespace rt
