#pragma once

#include <memory>

#include <tinyxml2/tinyxml2.hh>

#include <rt/theater/material/material_solid.hh>

namespace rt {

class MaterialSolidLoader {
 public:
  explicit MaterialSolidLoader(tinyxml2::XMLElement* element) noexcept;

  std::unique_ptr<MaterialSolid> Load();

 private:
  tinyxml2::XMLElement* element_;
  std::unique_ptr<MaterialSolid> material_;

  void LoadColor();
  void LoadPhong();
  void LoadReflectance();
  void LoadTransmittance();
  void LoadRefraction();
};

}  // namespace rt
