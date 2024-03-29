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
  double a = 0.0;
  double b = 0.0;
  u = std::modf(u, &a);
  v = std::modf(v, &b);
  auto x = static_cast<std::size_t>(u * image_->width());
  auto y = static_cast<std::size_t>(v * image_->height());
  return (*image_)[{x, y}];
}

std::string MaterialTextured::ToString() const {
  return "MaterialTextured";
}

}  // namespace rt
