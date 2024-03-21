#include "camera.hh"

namespace rt {

const Vector3<>& Camera::position() const noexcept {
  return position_;
}

const Vector3<>& Camera::lookat() const noexcept {
  return lookat_;
}

const Vector3<>& Camera::up() const noexcept {
  return up_;
}

const Angle<>& Camera::horizontal_fov() const noexcept {
  return horizontal_fov_;
}

std::size_t Camera::width() const noexcept {
  return width_;
}

std::size_t Camera::height() const noexcept {
  return height_;
}

std::size_t Camera::max_bounces() const noexcept {
  return max_bounces_;
}

Camera& Camera::SetPosition(const Vector3<>& value) noexcept {
  position_ = value;
  return *this;
}

Camera& Camera::SetLookat(const Vector3<>& value) noexcept {
  lookat_ = value;
  return *this;
}

Camera& Camera::SetUp(const Vector3<>& value) noexcept {
  up_ = value;
  return *this;
}

Camera& Camera::SetHorizontalFov(const Angle<>& value) noexcept {
  horizontal_fov_ = value;
  return *this;
}

Camera& Camera::SetResolution(std::size_t width, std::size_t height) noexcept {
  width_ = width;
  height_ = height;
  return *this;
}

Camera& Camera::SetMaxBounces(std::size_t value) noexcept {
  max_bounces_ = value;
  return *this;
}

std::string Camera::ToString() const {
  std::string str = "Camera\n";
  str += std::format("  position = {}\n", position_.ToString());
  str += std::format("  lookat = {}\n", lookat_.ToString());
  str += std::format("  up = {}\n", up_.ToString());
  str += std::format("  horizontal fov = {}\n", horizontal_fov_.ToString());
  str += std::format("  resolution = {} x {}\n", width_, height_);
  str += std::format("  max bounces = {}\n", max_bounces_);
  return str;
}

}  // namespace rt
