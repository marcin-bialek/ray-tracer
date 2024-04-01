#include "transformation_loader.hh"

#include <rt/common/exception.hh>
#include <rt/common/xml.hh>
#include <rt/transformations/rotate_x.hh>
#include <rt/transformations/rotate_y.hh>
#include <rt/transformations/rotate_z.hh>
#include <rt/transformations/scale.hh>
#include <rt/transformations/translate.hh>

namespace rt {

TransformationLoader::TransformationLoader(
    tinyxml2::XMLElement* element) noexcept
    : element_{element} {}

TransformationLoader::TransformationPtr TransformationLoader::Load() {
  auto i = loaders_.find(element_->Name());
  if (i == loaders_.end()) {
    throw RuntimeError{"unsupported transformation {}", element_->Name()};
  }
  return (this->*(i->second))();
}

bool TransformationLoader::IsTransformation(
    tinyxml2::XMLElement* element) noexcept {
  return loaders_.contains(element->Name());
}

TransformationLoader::TransformationPtr
TransformationLoader::LoadTranslation() {
  try {
    auto animation = GetOptionalAttr<std::string>(element_, "animation");
    if (animation.has_value()) {
      auto begin = GetAttrVector3<>(GetFirst(element_, "begin"));
      auto end = GetAttrVector3<>(GetFirst(element_, "end"));
      auto anim = LoadAnimation<Vector3<>>(element_, begin, end);
      return std::make_unique<Translate>(std::move(anim));
    }
    return std::make_unique<Translate>(GetAttrVector3<>(element_));
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading translation, {}", err.what()};
  }
}

TransformationLoader::TransformationPtr TransformationLoader::LoadScaling() {
  auto transformation = std::make_unique<Scale>();
  try {
    transformation->SetVector(GetAttrVector3<>(element_));
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading scaling, {}", err.what()};
  }
  return std::move(transformation);
}

TransformationLoader::TransformationPtr TransformationLoader::LoadRotationX() {
  auto transformation = std::make_unique<RotateX>();
  try {
    transformation->SetAngle(GetAttrAngle<>(element_, "theta"));
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading rotation X, {}", err.what()};
  }
  return std::move(transformation);
}

TransformationLoader::TransformationPtr TransformationLoader::LoadRotationY() {
  auto transformation = std::make_unique<RotateY>();
  try {
    transformation->SetAngle(GetAttrAngle<>(element_, "theta"));
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading rotation Y, {}", err.what()};
  }
  return std::move(transformation);
}

TransformationLoader::TransformationPtr TransformationLoader::LoadRotationZ() {
  auto transformation = std::make_unique<RotateZ>();
  try {
    transformation->SetAngle(GetAttrAngle<>(element_, "theta"));
  } catch (const std::exception& err) {
    throw RuntimeError{"error loading rotation Z, {}", err.what()};
  }
  return std::move(transformation);
}

const std::map<std::string, TransformationLoader::LoaderPtr>
    TransformationLoader::loaders_{
        {"translate", &TransformationLoader::LoadTranslation},
        {"scale", &TransformationLoader::LoadScaling},
        {"rotateX", &TransformationLoader::LoadRotationX},
        {"rotateY", &TransformationLoader::LoadRotationY},
        {"rotateZ", &TransformationLoader::LoadRotationZ},
    };

}  // namespace rt
