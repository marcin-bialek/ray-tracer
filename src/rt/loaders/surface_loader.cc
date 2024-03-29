#include "surface_loader.hh"

#include <rt/common/exception.hh>
#include <rt/common/xml.hh>
#include <rt/theater/surfaces/mesh.hh>
#include <rt/theater/surfaces/sphere.hh>

#include "material_loader.hh"
#include "obj_loader.hh"

namespace rt {

SurfaceLoader::SurfaceLoader(tinyxml2::XMLElement* element,
                             const std::filesystem::path& directory) noexcept
    : element_{element}, directory_{directory} {}

SurfaceLoader::SurfacePtr SurfaceLoader::Load() {
  auto i = loaders_.find(element_->Name());
  if (i == loaders_.end()) {
    throw RuntimeError{"unsupported surface {}", element_->Name()};
  }
  auto surface = (this->*(i->second))();
  auto element_material = GetFirstChildIf(
      element_, [](auto e) { return MaterialLoader::IsMaterial(e); });
  if (!element_material) {
    throw RuntimeError{"no material"};
  }
  MaterialLoader material_loader{element_material, directory_};
  surface->SetMaterial(material_loader.Load());
  return std::move(surface);
}

bool SurfaceLoader::IsSurface(tinyxml2::XMLElement* element) noexcept {
  return loaders_.contains(element->Name());
}

SurfaceLoader::SurfacePtr SurfaceLoader::LoadSphere() {
  auto surface = std::make_unique<Sphere>();
  try {
    surface->SetRadius(GetAttr<double>(element_, "radius"));
    surface->SetPosition(FirstGetAttrVector3<>(element_, "position"));
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading sphere, {}", err.what()};
  }
  return std::move(surface);
}

SurfaceLoader::SurfacePtr SurfaceLoader::LoadMesh() {
  auto surface = std::make_unique<Mesh>();
  try {
    OBJLoader obj_loader{};
    auto name = GetAttr<std::string>(element_, "name");
    auto result = obj_loader.FromFile(directory_ / name);
    surface->SetTriangles(std::move(result.triangles));
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading mesh, {}", err.what()};
  }
  return std::move(surface);
}

const std::map<std::string, SurfaceLoader::LoaderPtr> SurfaceLoader::loaders_{
    {"sphere", &SurfaceLoader::LoadSphere},
    {"mesh", &SurfaceLoader::LoadMesh},
};

}  // namespace rt
