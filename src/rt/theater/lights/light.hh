#pragma once

#include <string>

namespace rt {

class Light {
 public:
  virtual ~Light() noexcept = default;

  virtual std::string ToString() const = 0;
};

}  // namespace rt
