#pragma once

#include <memory>

#include <tinyxml2/tinyxml2.hh>

#include <rt/theater/surfaces/sphere.hh>

namespace rt {

class SphereLoader {
 public:
  explicit SphereLoader(tinyxml2::XMLElement* element) noexcept;

  std::unique_ptr<Sphere> Load();

 private:
  tinyxml2::XMLElement* element_;
  std::unique_ptr<Sphere> sphere_;

  void LoadPosition();
  void LoadRadius();
  void LoadMaterial();
};

}  // namespace rt