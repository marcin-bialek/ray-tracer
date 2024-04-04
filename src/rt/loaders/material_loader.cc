#include "material_loader.hh"

#include <rt/common/exception.hh>
#include <rt/common/xml.hh>
#include <rt/material/material_solid.hh>
#include <rt/material/material_textured.hh>

#include "image_loader.hh"

namespace rt {

MaterialLoader::MaterialLoader(tinyxml2::XMLElement* element,
                               const std::filesystem::path& directory) noexcept
    : element_{element}, directory_{directory} {}

MaterialLoader::MaterialPtr MaterialLoader::Load() {
  auto i = loaders_.find(element_->Name());
  if (i == loaders_.end()) {
    throw RuntimeError{"unsupported material {}", element_->Name()};
  }
  auto material = (this->*(i->second))();
  material->SetPhong(FirstGetAttr<double>(element_, "phong", "ka"),
                     FirstGetAttr<double>(element_, "phong", "kd"),
                     FirstGetAttr<double>(element_, "phong", "ks"),
                     FirstGetAttr<double>(element_, "phong", "exponent"));
  material->SetReflectance(FirstGetAttr<double>(element_, "reflectance", "r"));
  material->SetTransmittance(
      FirstGetAttr<double>(element_, "transmittance", "t"));
  material->SetRefraction(FirstGetAttr<double>(element_, "refraction", "iof"));
  return std::move(material);
}

bool MaterialLoader::IsMaterial(tinyxml2::XMLElement* element) noexcept {
  return loaders_.contains(element->Name());
}

MaterialLoader::MaterialPtr MaterialLoader::LoadMaterialSolid() {
  auto material = std::make_unique<MaterialSolid>();
  try {
    material->SetColor(FirstGetAttrColor<>(element_, "color"));
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading material solid, {}", err.what()};
  }
  return std::move(material);
}

MaterialLoader::MaterialPtr MaterialLoader::LoadMaterialTextured() {
  auto material = std::make_unique<MaterialTextured>();
  try {
    auto name = FirstGetAttr<std::string>(element_, "texture", "name");
    ImageLoader loader{directory_ / name};
    material->SetImage(loader.Load());
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading material textured, {}", err.what()};
  }
  return std::move(material);
}

const std::map<std::string, MaterialLoader::LoaderPtr> MaterialLoader::loaders_{
    {"material_solid", &MaterialLoader::LoadMaterialSolid},
    {"material_textured", &MaterialLoader::LoadMaterialTextured},
};

}  // namespace rt
