#pragma once

#include <map>
#include <memory>
#include <string>

#include <tinyxml2/tinyxml2.hh>

#include <rt/animations/animation.hh>
#include <rt/animations/linear_animation.hh>
#include <rt/common/exception.hh>
#include <rt/common/xml.hh>
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

  template <typename Tp, typename... Args>
  std::unique_ptr<Animation<Tp>> LoadAnimation(tinyxml2::XMLElement* element,
                                               Args&&... args) {
    std::unique_ptr<Animation<Tp>> anim{};
    auto type = GetAttr<std::string>(element_, "animation");
    if (type == "linear") {
      anim = std::make_unique<LinearAnimation<Tp>>(std::forward<Args>(args)...);
    } else {
      throw RuntimeError{"unknown animation {}", type};
    }
    anim->SetDuration(std::chrono::milliseconds{
        GetOptionalAttr<std::size_t>(element_, "duration").value_or(0)});
    anim->SetDelay(std::chrono::milliseconds{
        GetOptionalAttr<std::size_t>(element_, "delay").value_or(0)});
    anim->SetIterations(GetOptionalAttr<std::size_t>(element_, "iterations")
                            .value_or(std::numeric_limits<std::size_t>::max()));
    return std::move(anim);
  }

  using LoaderPtr = TransformationPtr (TransformationLoader::*)();
  static const std::map<std::string, LoaderPtr> loaders_;
};

}  // namespace rt
