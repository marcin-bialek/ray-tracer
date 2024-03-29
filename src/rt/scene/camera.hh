#pragma once

#include <cstdlib>
#include <string>

#include <rt/math/angle.hh>
#include <rt/math/vector3.hh>

namespace rt {

struct Viewport {
  Vector3<> origin;
  Vector3<> u;
  Vector3<> v;
};

class Camera {
 public:
  static constexpr Angle<> kDefaultHorizontalFov = 45.0f;
  static constexpr std::size_t kDefaultWidth = 1920;
  static constexpr std::size_t kDefaultHeight = 1080;
  static constexpr std::size_t kDefaultMaxBounces = 10;

  explicit Camera() noexcept = default;

  const Vector3<>& position() const noexcept;
  const Vector3<>& lookat() const noexcept;
  const Vector3<>& up() const noexcept;
  const Angle<>& horizontal_fov() const noexcept;
  std::size_t width() const noexcept;
  std::size_t height() const noexcept;
  std::size_t max_bounces() const noexcept;
  double aspect_ratio() const noexcept;
  double focal_length() const noexcept;
  Viewport viewport() const noexcept;

  Camera& SetPosition(const Vector3<>& value) noexcept;
  Camera& SetLookat(const Vector3<>& value) noexcept;
  Camera& SetUp(const Vector3<>& value) noexcept;
  Camera& SetHorizontalFov(const Angle<>& value) noexcept;
  Camera& SetResolution(std::size_t width, std::size_t height) noexcept;
  Camera& SetMaxBounces(std::size_t value) noexcept;

  std::string ToString() const;

 private:
  Vector3<> position_{};
  Vector3<> lookat_{};
  Vector3<> up_{};
  Angle<> horizontal_fov_{kDefaultHorizontalFov};
  std::size_t width_{kDefaultWidth};
  std::size_t height_{kDefaultHeight};
  std::size_t max_bounces_{kDefaultMaxBounces};
};

}  // namespace rt
