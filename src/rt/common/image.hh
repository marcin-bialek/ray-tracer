#pragma once

#include <vector>

#include "color.hh"

namespace rt {

class Image {
 public:
  explicit Image(std::size_t width, std::size_t height, Color color = {});

  std::size_t width() const noexcept;
  std::size_t height() const noexcept;

  std::vector<uint8_t> ToRGBBuffer() const;

  Color& operator[](std::pair<std::size_t, std::size_t> position);
  const Color& operator[](std::pair<std::size_t, std::size_t> position) const;

 private:
  std::vector<std::vector<Color>> data_;
  std::size_t width_;
  std::size_t height_;
};

}  // namespace rt
