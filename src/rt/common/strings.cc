#include "strings.h"

#include <cctype>
#include <ranges>

namespace rt {

static bool IsNotGraph(char c) {
  return !std::isgraph(c);
}

std::string Trim(std::string_view text) noexcept {
  auto t = text | std::views::drop_while(IsNotGraph) | std::views::reverse |
           std::views::drop_while(IsNotGraph) | std::views::reverse;
  return {t.begin(), t.end()};
}

std::vector<std::string> Split(std::string_view text,
                               std::string_view delim) noexcept {
  std::vector<std::string> result{};
  for (auto part : std::views::split(text, delim)) {
    result.emplace_back(part.begin(), part.end());
  }
  return result;
}

std::string Lowercase(std::string_view text) noexcept {
  auto t = text | std::views::transform([](char c) {
             return static_cast<char>(std::tolower(c));
           });
  return {t.begin(), t.end()};
}

}  // namespace rt
