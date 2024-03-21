#include "camera_loader.hh"

#include <iostream>
#include <string>

#include <rt/common/exception.hh>

#include "common.hh"

namespace rt {

CameraLoader::CameraLoader(tinyxml2::XMLElement* element) noexcept
    : element_{element} {}

std::unique_ptr<Camera> CameraLoader::Load() {
  camera_ = std::make_unique<Camera>();
  try {
    LoadPosition();
    LoadLookat();
    LoadUp();
    LoadHorizontalFov();
    LoadResolution();
    LoadMaxBounces();
  } catch (std::exception& err) {
    throw RuntimeError{"error loading camera: {}", err.what()};
  }
  return std::move(camera_);
}

void CameraLoader::LoadPosition() {
  auto elm_position = element_->FirstChildElement("position");
  if (elm_position) {
    auto value = details::LoadVector3(elm_position);
    camera_->SetPosition(value);
  } else {
    std::cerr << "Warning: camera's position is not set." << std::endl;
  }
}

void CameraLoader::LoadLookat() {
  auto elm_lookat = element_->FirstChildElement("lookat");
  if (elm_lookat) {
    auto value = details::LoadVector3(elm_lookat);
    camera_->SetLookat(value);
  } else {
    std::cerr << "Warning: camera's lookat is not set." << std::endl;
  }
}

void CameraLoader::LoadUp() {
  auto elm_up = element_->FirstChildElement("up");
  if (elm_up) {
    auto value = details::LoadVector3(elm_up);
    camera_->SetUp(value);
  } else {
    std::cerr << "Warning: camera's up is not set." << std::endl;
  }
}

void CameraLoader::LoadHorizontalFov() {
  auto elm_horizontal_fov = element_->FirstChildElement("horizontal_fov");
  if (elm_horizontal_fov) {
    auto value = std::stof(elm_horizontal_fov->Attribute("angle"));
    camera_->SetHorizontalFov(value);
  } else {
    std::cerr << "Warning: camera's horizontal_fov is not set." << std::endl;
  }
}

void CameraLoader::LoadResolution() {
  auto elm_resolution = element_->FirstChildElement("resolution");
  if (elm_resolution) {
    auto width = std::stoul(elm_resolution->Attribute("horizontal"));
    auto height = std::stoul(elm_resolution->Attribute("vertical"));
    camera_->SetResolution(width, height);
  } else {
    std::cerr << "Warning: camera's resolution is not set." << std::endl;
  }
}

void CameraLoader::LoadMaxBounces() {
  auto elm_max_bounces = element_->FirstChildElement("max_bounces");
  if (elm_max_bounces) {
    auto value = std::stoul(elm_max_bounces->Attribute("n"));
    camera_->SetMaxBounces(value);
  } else {
    std::cerr << "Warning: camera's max_bounces is not set." << std::endl;
  }
}

}  // namespace rt
