#include "renderer.hh"

namespace rt {

Image Renderer::Render(const Scene& scene) {
  Image image{scene.camera()->width(), scene.camera()->height(),
              scene.background()};
  return image;
}

}  // namespace rt
