#pragma once

#include <filesystem>
#include <memory>

#include <tinyxml2/tinyxml2.hh>

#include <rt/theater/material/material_textured.hh>

namespace rt {

class MaterialTexturedLoader {
 public:
  explicit MaterialTexturedLoader(
      tinyxml2::XMLElement* element,
      const std::filesystem::path& directory) noexcept;

  std::unique_ptr<MaterialTextured> Load();

 private:
  tinyxml2::XMLElement* element_;
  std::filesystem::path directory_;
  std::unique_ptr<MaterialTextured> material_;

  void LoadTexture();
  void LoadPhong();
  void LoadReflectance();
  void LoadTransmittance();
  void LoadRefraction();
};

}  // namespace rt
