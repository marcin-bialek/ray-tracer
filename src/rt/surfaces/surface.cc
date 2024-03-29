#include "surface.hh"

namespace rt {

const Material* Surface::material() const noexcept {
  return material_.get();
}

Surface& Surface::SetMaterial(std::unique_ptr<Material> material) noexcept {
  material_ = std::move(material);
  return *this;
}

Surface& Surface::AddTransformation(
    std::unique_ptr<Transformation> transformation) noexcept {
  transformations_.push_back(std::move(transformation));
  return *this;
}

}  // namespace rt
