#pragma once

#include <rt/common/image.hh>
#include <rt/theater/scene.hh>

namespace rt {

class Renderer {
 public:
  explicit Renderer() noexcept = default;

  Image Render(const Scene& scene);

 private:
};

}  // namespace rt
