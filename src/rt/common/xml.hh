#pragma once

#include <limits>
#include <string>

#include <tinyxml2/tinyxml2.hh>

#include <rt/math/angle.hh>
#include <rt/math/vector3.hh>

#include "concepts.hh"
#include "exception.hh"

namespace rt {

namespace details {

inline void ThrowIfError(tinyxml2::XMLElement* element) {
  if (element->GetDocument()->Error()) {
    throw RuntimeError{"{}", element->GetDocument()->ErrorStr()};
  }
}

template <typename Tp>
struct AttrGetter {};

template <>
struct AttrGetter<std::string> {
  static std::string Get(tinyxml2::XMLElement* element, std::string_view name) {
    const char* value{};
    element->QueryStringAttribute(name.data(), &value);
    ThrowIfError(element);
    return value;
  }
};

template <>
struct AttrGetter<bool> {
  static bool Get(tinyxml2::XMLElement* element, std::string_view name) {
    bool value{};
    element->QueryBoolAttribute(name.data(), &value);
    ThrowIfError(element);
    return value;
  }
};

template <std::unsigned_integral Tp>
struct AttrGetter<Tp> {
  static Tp Get(tinyxml2::XMLElement* element, std::string_view name) {
    uint64_t value{};
    element->QueryUnsigned64Attribute(name.data(), &value);
    ThrowIfError(element);
    if (std::numeric_limits<Tp>::max() < value) {
      throw RuntimeError{"value {} does not fit specified type", value};
    }
    return static_cast<Tp>(value);
  }
};

template <std::signed_integral Tp>
struct AttrGetter<Tp> {
  static Tp Get(tinyxml2::XMLElement* element, std::string_view name) {
    int64_t value{};
    element->QueryInt64Attribute(name.data(), &value);
    ThrowIfError(element);
    if (value < std::numeric_limits<Tp>::min() ||
        std::numeric_limits<Tp>::max() < value) {
      throw RuntimeError{"value {} does not fit specified type", value};
    }
    return static_cast<Tp>(value);
  }
};

template <std::floating_point Tp>
struct AttrGetter<Tp> {
  static Tp Get(tinyxml2::XMLElement* element, std::string_view name) {
    double value{};
    element->QueryDoubleAttribute(name.data(), &value);
    ThrowIfError(element);
    return static_cast<Tp>(value);
  }
};

template <Numeric Tp>
struct AttrGetter<Vector3<Tp>> {
  static Vector3<Tp> Get(tinyxml2::XMLElement* element, std::string_view x,
                         std::string_view y, std::string_view z) {
    Vector3<Tp> value{};
    value.x = AttrGetter<Tp>::Get(element, x);
    value.y = AttrGetter<Tp>::Get(element, y);
    value.z = AttrGetter<Tp>::Get(element, z);
    return value;
  }
};

template <Numeric Tp>
struct AttrGetter<Angle<Tp>> {
  static Angle<Tp> Get(tinyxml2::XMLElement* element, std::string_view name,
                       bool degrees) {
    Angle<Tp> value{};
    if (degrees) {
      value.SetDegrees(AttrGetter<Tp>::Get(element, name));
    } else {
      value.SetRadians(AttrGetter<Tp>::Get(element, name));
    }
    return value;
  }
};

template <typename Tp>
concept GetFirstChildIfFunc = requires(Tp callback) {
  {
    callback(std::declval<tinyxml2::XMLElement*>())
  } -> std::convertible_to<bool>;
};

template <typename Tp>
concept ForeachChildFunc =
    requires(Tp callback) { callback(std::declval<tinyxml2::XMLElement*>()); };

}  // namespace details

tinyxml2::XMLElement* GetFirst(tinyxml2::XMLElement* element,
                               std::string_view name);

template <typename Tp>
auto GetAttr(tinyxml2::XMLElement* element, std::string_view name) {
  return details::AttrGetter<Tp>::Get(element, name);
}

template <Numeric Tp = double>
auto GetAttrVector3(tinyxml2::XMLElement* element, std::string_view x = "x",
                    std::string_view y = "y", std::string_view z = "z") {
  return details::AttrGetter<Vector3<Tp>>::Get(element, x, y, z);
}

template <Numeric Tp = double>
auto GetAttrColor(tinyxml2::XMLElement* element) {
  return GetAttrVector3<Tp>(element, "r", "g", "b");
}

template <Numeric Tp = double>
auto GetAttrAngle(tinyxml2::XMLElement* element, std::string_view name,
                  bool degrees = true) {
  return details::AttrGetter<Angle<Tp>>::Get(element, name, degrees);
}

template <typename Tp>
auto FirstGetAttr(tinyxml2::XMLElement* element, std::string_view name,
                  std::string_view attr_name) {
  return GetAttr<Tp>(GetFirst(element, name), attr_name);
}

template <Numeric Tp = double>
auto FirstGetAttrVector3(tinyxml2::XMLElement* element, std::string_view name,
                         std::string_view x = "x", std::string_view y = "y",
                         std::string_view z = "z") {
  return GetAttrVector3<Tp>(GetFirst(element, name), x, y, z);
}

template <Numeric Tp = double>
auto FirstGetAttrColor(tinyxml2::XMLElement* element, std::string_view name) {
  return GetAttrColor<Tp>(GetFirst(element, name));
}

template <Numeric Tp = double>
auto FirstGetAttrAngle(tinyxml2::XMLElement* element, std::string_view name,
                       std::string_view attr_name, bool degrees = true) {
  return GetAttrAngle<Tp>(GetFirst(element, name), attr_name, degrees);
}

template <details::GetFirstChildIfFunc Func>
auto GetFirstChildIf(tinyxml2::XMLElement* element, Func&& test) {
  auto e = element->FirstChildElement();
  while (e && !test(e)) {
    e = e->NextSiblingElement();
  }
  return e;
}

template <details::ForeachChildFunc Func>
void ForeachChild(tinyxml2::XMLElement* element, Func&& callback) {
  auto e = element->FirstChildElement();
  while (e) {
    callback(e);
    e = e->NextSiblingElement();
  }
}

}  // namespace rt
