#include "sphere_loader.hh"

#include <rt/common/exception.hh>

#include "common.hh"
#include "material_solid_loader.hh"
#include "material_textured_loader.hh"

namespace rt {

SphereLoader::SphereLoader(tinyxml2::XMLElement* element,
                           const std::filesystem::path& directory) noexcept
    : element_{element}, directory_{directory} {}

std::unique_ptr<Sphere> SphereLoader::Load() {
  sphere_ = std::make_unique<Sphere>();
  try {
    LoadPosition();
    LoadRadius();
    LoadMaterial();
  } catch (std::exception& err) {
    throw RuntimeError{"error loading sphere: {}", err.what()};
  }
  return std::move(sphere_);
}

void SphereLoader::LoadPosition() {
  auto elm_position = element_->FirstChildElement("position");
  if (elm_position) {
    sphere_->SetPosition(details::LoadVector3(elm_position));
  } else {
    throw RuntimeError{"position is not set"};
  }
}

void SphereLoader::LoadRadius() {
  sphere_->SetRadius(element_->DoubleAttribute("radius"));
}

void SphereLoader::LoadMaterial() {
  tinyxml2::XMLElement* elm = nullptr;
  if ((elm = element_->FirstChildElement("material_solid"))) {
    MaterialSolidLoader loader{elm};
    sphere_->SetMaterial(loader.Load());
  } else if ((elm = element_->FirstChildElement("material_textured"))) {
    MaterialTexturedLoader loader{elm, directory_};
    sphere_->SetMaterial(loader.Load());
  } else {
    throw RuntimeError{"material is not set"};
  }
}

}  // namespace rt
