#pragma once

#include <rt/common/color.hh>

#include "light.hh"

namespace rt {

class AmbientLight final : public Light {
 public:
  explicit AmbientLight() = default;

  const Color& color() const noexcept;

  AmbientLight& SetColor(const Color& value) noexcept;

  std::string ToString() const override;

 public:
  Color color_;
};

}  // namespace rt
