#pragma once

#include <map>
#include <memory>
#include <string>

#include <tinyxml2/tinyxml2.hh>

#include <rt/transformations/transformation.hh>

namespace rt {

class TransformationLoader {
 public:
  using TransformationPtr = std::unique_ptr<Transformation>;

  explicit TransformationLoader(tinyxml2::XMLElement* element) noexcept;

  TransformationPtr Load();

  static bool IsTransformation(tinyxml2::XMLElement* element) noexcept;

 private:
  tinyxml2::XMLElement* element_;

  TransformationPtr LoadTranslation();
  TransformationPtr LoadScaling();
  TransformationPtr LoadRotationX();
  TransformationPtr LoadRotationY();
  TransformationPtr LoadRotationZ();

  using LoaderPtr = TransformationPtr (TransformationLoader::*)();
  static const std::map<std::string, LoaderPtr> loaders_;
};

}  // namespace rt
