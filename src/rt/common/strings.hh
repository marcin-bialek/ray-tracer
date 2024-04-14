#pragma once

#include <string>
#include <vector>

namespace rt {

std::string Trim(std::string_view text) noexcept;
std::vector<std::string> Split(std::string_view text,
                               std::string_view delim) noexcept;
std::string Lowercase(std::string_view text) noexcept;

}  // namespace rt
