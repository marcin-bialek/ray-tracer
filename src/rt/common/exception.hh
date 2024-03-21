#pragma once

#include <format>
#include <stdexcept>

namespace rt {

class RuntimeError : public std::exception {
 public:
  template <typename... Args>
  explicit RuntimeError(std::format_string<Args...> format, Args&&... args) {
    message_ = std::format(format, std::forward<Args>(args)...);
  }

  const char* what() const noexcept override {
    return message_.c_str();
  }

 private:
  std::string message_;
};

}  // namespace rt
