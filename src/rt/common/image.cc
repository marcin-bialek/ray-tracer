#include "image.hh"

#include <cmath>

namespace rt {

Image::Image(std::size_t width, std::size_t height)
    : width_{width}, height_{height} {
  data_.resize(height);
  for (auto& row : data_) {
    row.resize(width);
  }
}

std::size_t Image::width() const noexcept {
  return width_;
}

std::size_t Image::height() const noexcept {
  return height_;
}

std::vector<uint8_t> Image::ToRGBABuffer() const {
  std::vector<uint8_t> buffer(4 * width_ * height_, 0);
  auto p = buffer.begin();
  for (auto& row : data_) {
    for (auto& pixel : row) {
      auto c = pixel.Clamp(0.0, 1.0);
      *p++ = static_cast<std::size_t>(255.0 * c.x);
      *p++ = static_cast<std::size_t>(255.0 * c.y);
      *p++ = static_cast<std::size_t>(255.0 * c.z);
      *p++ = 255;
    }
  }
  return buffer;
}

Vector3<>& Image::operator[](
    const std::pair<std::size_t, std::size_t>& position) {
  return data_[position.second][position.first];
}

const Vector3<>& Image::operator[](
    const std::pair<std::size_t, std::size_t>& position) const {
  return data_[position.second][position.first];
}

}  // namespace rt
