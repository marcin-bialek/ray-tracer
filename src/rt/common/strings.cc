#include "strings.h"

#include <cctype>
#include <ranges>

namespace rt {

static bool IsNotGraph(char c) {
  return !std::isgraph(c);
}

std::string Trim(std::string_view text) {
  auto t = text | std::views::drop_while(IsNotGraph) | std::views::reverse |
           std::views::drop_while(IsNotGraph) | std::views::reverse;
  return {t.begin(), t.end()};
}

std::vector<std::string> Split(std::string_view text, std::string_view delim) {
  std::vector<std::string> result{};
  for (auto part : std::views::split(text, delim)) {
    result.emplace_back(part.begin(), part.end());
  }
  return result;
}

}  // namespace rt
