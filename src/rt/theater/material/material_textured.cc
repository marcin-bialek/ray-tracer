#include "material_textured.hh"

namespace rt {

const Image* MaterialTextured::image() const noexcept {
  return image_.get();
}

MaterialTextured& MaterialTextured::SetImage(
    std::unique_ptr<Image> image) noexcept {
  image_ = std::move(image);
  return *this;
}

Vector3<> MaterialTextured::GetColor(double u, double v) const {
  u = std::clamp(u, 0.0, 1.0);
  v = std::clamp(v, 0.0, 1.0);
  auto x = static_cast<std::size_t>(u * image_->width());
  auto y = static_cast<std::size_t>(v * image_->height());
  return (*image_)[{x, y}];
}

std::string MaterialTextured::ToString() const {
  return "MaterialTextured";
}

}  // namespace rt
