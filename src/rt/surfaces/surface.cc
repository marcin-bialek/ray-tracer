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
    const Transformation& transformation) noexcept {
  return *this;
}

std::optional<Intersection> Surface::Hit(const Ray& ray) const {
  return DoHit(ray);
}

}  // namespace rt
