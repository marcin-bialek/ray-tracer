#pragma once

#include <concepts>

namespace rt {

template <typename Tp>
concept Numeric = std::integral<Tp> || std::floating_point<Tp>;

template <typename Tp>
concept Arithmetic = requires(Tp value) {
  { -std::declval<Tp>() } -> std::convertible_to<Tp>;
  { std::declval<Tp>() + std::declval<Tp>() } -> std::convertible_to<Tp>;
  { std::declval<Tp>() - std::declval<Tp>() } -> std::convertible_to<Tp>;
  { std::declval<Tp>() * std::declval<Tp>() } -> std::convertible_to<Tp>;
  { std::declval<Tp>() / std::declval<Tp>() } -> std::convertible_to<Tp>;
};

}  // namespace rt
