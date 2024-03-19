#pragma once

#include <cstdlib>

#include <rt/math/vector3.hh>

namespace rt {

class Camera {
 public:
  static constexpr std::size_t kDefaultWidth = 1920;
  static constexpr std::size_t kDefaultHeight = 1080;
  static constexpr std::size_t kDefaultMaxBounces = 10;
  static constexpr float kDefaultHorizontalFov = 45.0f;

  explicit Camera() noexcept = default;

  Vector3<> position() const noexcept;
  Vector3<> lookat() const noexcept;
  Vector3<> up() const noexcept;
  std::size_t width() const noexcept;
  std::size_t height() const noexcept;
  std::size_t max_bounces() const noexcept;
  float horizontal_fov() const noexcept;

  Camera& SetPosition(const Vector3<>& value) noexcept;
  Camera& SetLookat(const Vector3<>& value) noexcept;
  Camera& SetUp(const Vector3<>& value) noexcept;
  Camera& SetResolution(std::size_t width, std::size_t height) noexcept;
  Camera& SetMaxBounces(std::size_t value) noexcept;
  Camera& SetHorizontalFov(float value) noexcept;

 private:
  Vector3<> position_{};
  Vector3<> lookat_{};
  Vector3<> up_{};
  std::size_t width_{kDefaultWidth};
  std::size_t height_{kDefaultHeight};
  std::size_t max_bounces_{kDefaultMaxBounces};
  float horizontal_fov_{kDefaultHorizontalFov};
};

}  // namespace rt
