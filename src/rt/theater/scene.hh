#pragma once

#include <memory>
#include <string>
#include <vector>

#include "camera.hh"
#include "lights/light.hh"

namespace rt {

class Scene {
 public:
  explicit Scene() noexcept = default;

  Scene& SetCamera(std::unique_ptr<Camera> camera) noexcept;
  Scene& AddLight(std::unique_ptr<Light> light) noexcept;

  std::string ToString() const;

 private:
  std::unique_ptr<Camera> camera_;
  std::vector<std::unique_ptr<Light>> lights_;
};

}  // namespace rt
