#pragma once

#include <string>
#include <vector>

namespace rt {

std::string Trim(std::string_view text);
std::vector<std::string> Split(std::string_view text, std::string_view delim);

}  // namespace rt
