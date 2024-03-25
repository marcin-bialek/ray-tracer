#pragma once

#include <filesystem>
#include <span>
#include <string>

#include <rt/math/vector3.hh>
#include <rt/theater/surfaces/triangle.hh>

namespace rt {

class OBJLoader {
 public:
  struct Result {
    std::vector<Triangle> triangles;
  };

  explicit OBJLoader() noexcept = default;

  Result FromString(std::string_view source);
  Result FromFile(const std::filesystem::path& path);

 private:
  std::vector<Vector3<>> vertices_;
  std::vector<Vector3<>> texture_coords_;
  std::vector<Vector3<>> normals_;
  std::vector<Triangle> triangles_;

  void ParseLine(std::size_t i, std::span<std::string> parts);
  void ParseVertex(std::size_t i, std::span<std::string> parts);
  void ParseTextureCoords(std::size_t i, std::span<std::string> parts);
  void ParseNormals(std::size_t i, std::span<std::string> parts);
  void ParseFace(std::size_t i, std::span<std::string> parts);
};

}  // namespace rt
