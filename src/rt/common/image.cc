#include "image.hh"

namespace rt {

Image::Image(std::size_t width, std::size_t height, Color color)
    : width_{width}, height_{height} {
  data_.resize(height);
  for (auto& row : data_) {
    row.resize(width, color);
  }
}

std::size_t Image::width() const noexcept {
  return width_;
}

std::size_t Image::height() const noexcept {
  return height_;
}

std::vector<uint8_t> Image::ToRGBBuffer() const {
  std::vector<uint8_t> buffer(3 * width_ * height_, 0);
  auto p = buffer.begin();
  for (auto& row : data_) {
    for (auto& pixel : row) {
      *p++ = pixel.r;
      *p++ = pixel.g;
      *p++ = pixel.b;
    }
  }
  return buffer;
}

Color& Image::operator[](std::pair<std::size_t, std::size_t> position) {
  return data_[position.second][position.first];
}

const Color& Image::operator[](
    std::pair<std::size_t, std::size_t> position) const {
  return data_[position.second][position.first];
}

}  // namespace rt
