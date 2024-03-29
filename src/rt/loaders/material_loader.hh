#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <string>

#include <tinyxml2/tinyxml2.hh>

#include <rt/material/material.hh>

namespace rt {

class MaterialLoader {
 public:
  using MaterialPtr = std::unique_ptr<Material>;

  explicit MaterialLoader(tinyxml2::XMLElement* element,
                          const std::filesystem::path& directory) noexcept;

  MaterialPtr Load();

  static bool IsMaterial(tinyxml2::XMLElement* element) noexcept;

 private:
  tinyxml2::XMLElement* element_;
  std::filesystem::path directory_;

  MaterialPtr LoadMaterialSolid();
  MaterialPtr LoadMaterialTextured();

  using LoaderPtr = MaterialPtr (MaterialLoader::*)();
  static const std::map<std::string, LoaderPtr> loaders_;
};

}  // namespace rt
