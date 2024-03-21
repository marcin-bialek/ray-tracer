#pragma once

#include <concepts>

namespace rt {

template <typename Tp>
concept Numeric = std::integral<Tp> || std::floating_point<Tp>;

}
