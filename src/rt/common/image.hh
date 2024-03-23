#pragma once

#include <vector>

#include <rt/math/vector3.hh>

namespace rt {

class Image {
 public:
  explicit Image(std::size_t width, std::size_t height);

  std::size_t width() const noexcept;
  std::size_t height() const noexcept;

  std::vector<uint8_t> ToRGBBuffer() const;

  Vector3<>& operator[](std::pair<std::size_t, std::size_t> position);
  const Vector3<>& operator[](
      std::pair<std::size_t, std::size_t> position) const;

 private:
  std::vector<std::vector<Vector3<>>> data_;
  std::size_t width_;
  std::size_t height_;
};

}  // namespace rt
