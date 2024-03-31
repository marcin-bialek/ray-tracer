#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <string>

#include <tinyxml2/tinyxml2.hh>

#include <rt/surfaces/surface.hh>

namespace rt {

class SurfaceLoader {
 public:
  using SurfacePtr = std::unique_ptr<Surface>;

  explicit SurfaceLoader(tinyxml2::XMLElement* element,
                         const std::filesystem::path& directory) noexcept;

  SurfacePtr Load();

  static bool IsSurface(tinyxml2::XMLElement* element) noexcept;

 private:
  tinyxml2::XMLElement* element_;
  std::filesystem::path directory_;

  SurfacePtr LoadSphere();
  SurfacePtr LoadMesh();
  void LoadMaterial(Surface* surface);
  void LoadTransformations(Surface* surface);

  using LoaderPtr = SurfacePtr (SurfaceLoader::*)();
  static const std::map<std::string, LoaderPtr> loaders_;
};

}  // namespace rt
