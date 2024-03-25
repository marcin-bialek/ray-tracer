#pragma once

#include <filesystem>
#include <memory>

#include <tinyxml2/tinyxml2.hh>

#include <rt/theater/surfaces/mesh.hh>

namespace rt {

class MeshLoader {
 public:
  explicit MeshLoader(tinyxml2::XMLElement* element,
                      const std::filesystem::path& directory) noexcept;

  std::unique_ptr<Mesh> Load();

 private:
  tinyxml2::XMLElement* element_;
  std::filesystem::path directory_;
  std::unique_ptr<Mesh> mesh_;

  void LoadOBJ();
  void LoadMaterial();
};

}  // namespace rt
