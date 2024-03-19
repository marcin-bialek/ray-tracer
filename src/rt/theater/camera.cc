#include "camera.hh"

namespace rt {

Vector3<> Camera::position() const noexcept {
  return position_;
}

Vector3<> Camera::lookat() const noexcept {
  return lookat_;
}

Vector3<> Camera::up() const noexcept {
  return up_;
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

float Camera::horizontal_fov() const noexcept {
  return horizontal_fov_;
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

Camera& Camera::SetResolution(std::size_t width, std::size_t height) noexcept {
  width_ = width;
  height_ = height;
  return *this;
}

Camera& Camera::SetMaxBounces(std::size_t value) noexcept {
  max_bounces_ = value;
  return *this;
}

Camera& Camera::SetHorizontalFov(float value) noexcept {
  horizontal_fov_ = value;
  return *this;
}

}  // namespace rt
