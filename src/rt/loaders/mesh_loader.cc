#include "mesh_loader.hh"

#include <rt/common/exception.hh>

#include "common.hh"
#include "material_solid_loader.hh"
#include "obj_loader.hh"

namespace rt {

MeshLoader::MeshLoader(tinyxml2::XMLElement* element,
                       const std::filesystem::path& directory) noexcept
    : element_{element}, directory_{directory} {}

std::unique_ptr<Mesh> MeshLoader::Load() {
  mesh_ = std::make_unique<Mesh>();
  try {
    LoadOBJ();
    LoadMaterial();
  } catch (std::exception& err) {
    throw RuntimeError{"error loading mesh: {}", err.what()};
  }
  return std::move(mesh_);
}

void MeshLoader::LoadOBJ() {
  auto name = element_->Attribute("name");
  if (!name) {
    throw RuntimeError{"name is not set"};
  }
  OBJLoader loader{};
  auto result = loader.FromFile(directory_ / name);
  mesh_->SetTriangles(std::move(result.triangles));
}

void MeshLoader::LoadMaterial() {
  tinyxml2::XMLElement* elm = nullptr;
  if ((elm = element_->FirstChildElement("material_solid"))) {
    MaterialSolidLoader loader{elm};
    mesh_->SetMaterial(loader.Load());
  } else if ((elm = element_->FirstChildElement("material_textured"))) {
    throw RuntimeError{"material textured is not supported"};
  } else {
    throw RuntimeError{"material is not set"};
  }
}

}  // namespace rt
