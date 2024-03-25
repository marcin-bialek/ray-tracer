#include "obj_loader.hh"

#include <fstream>
#include <iostream>
#include <ranges>
#include <streambuf>

#include <rt/common/exception.hh>
#include <rt/common/strings.hh>

namespace rt {

OBJLoader::Result OBJLoader::FromString(std::string_view source) {
  auto lines = Split(source, "\n");
  for (std::size_t i = 0; i < lines.size(); ++i) {
    auto split = Split(lines[i], "#");
    if (!split.empty()) {
      auto parts = Split(Trim(split[0]), " ");
      parts.erase(std::remove(parts.begin(), parts.end(), ""), parts.end());
      if (!parts.empty()) {
        ParseLine(i, parts);
      }
    }
  }
  Result result{};
  result.triangles = std::move(triangles_);
  return result;
}

OBJLoader::Result OBJLoader::FromFile(const std::filesystem::path& path) {
  std::ifstream file{path};
  if (!file.good()) {
    throw RuntimeError{"could not open {}", path.c_str()};
  }
  std::string source{(std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>()};
  return FromString(source);
}

void OBJLoader::ParseLine(std::size_t i, std::span<std::string> parts) {
  if (parts[0] == "v") {
    ParseVertex(i, parts | std::views::drop(1));
  } else if (parts[0] == "vt") {
    ParseTextureCoords(i, parts | std::views::drop(1));
  } else if (parts[0] == "vn") {
    ParseNormals(i, parts | std::views::drop(1));
  } else if (parts[0] == "f") {
    ParseFace(i, parts | std::views::drop(1));
  } else {
    std::cout << "OBJ warning: unsupported element '" << parts[0] << "'"
              << std::endl;
  }
}

void OBJLoader::ParseVertex(std::size_t i, std::span<std::string> parts) {
  if (parts.size() < 3) {
    throw RuntimeError{"OBJ error (line {}): invalid vertex", i};
  }
  vertices_.emplace_back(std::stod(parts[0]), std::stod(parts[1]),
                         std::stod(parts[2]));
}

void OBJLoader::ParseTextureCoords(std::size_t i,
                                   std::span<std::string> parts) {
  if (parts.size() < 1) {
    throw RuntimeError{"OBJ error (line {}): invalid texture coordinates", i};
  }
  texture_coords_.emplace_back(
      std::stod(parts[0]), std::stod(parts.size() > 1 ? parts[1] : "0.0"), 0.0);
}

void OBJLoader::ParseNormals(std::size_t i, std::span<std::string> parts) {
  if (parts.size() < 3) {
    throw RuntimeError{"OBJ error (line {}): invalid normal", i};
  }
  normals_.emplace_back(std::stod(parts[0]), std::stod(parts[1]),
                        std::stod(parts[2]));
}

void OBJLoader::ParseFace(std::size_t i, std::span<std::string> parts) {
  if (parts.size() != 3) {
    throw RuntimeError{
        "OBJ error (line {}): invalid face, only triangles are supported", i};
  }
  auto& face = triangles_.emplace_back();
  for (std::size_t j = 0; j < 3; ++j) {
    auto indices = Split(parts[j], "/");
    if (indices.size() != 3) {
      throw RuntimeError{"OBJ error (line {}): invalid face data ({})", i, j};
    }
    auto iv = std::stoul(indices[0]);
    auto it = std::stoul(indices[1]);
    auto in = std::stoul(indices[2]);
    if (iv == 0 || iv > vertices_.size()) {
      throw RuntimeError{"OBJ error (line {}): invalid vertex index {}", i, iv};
    }
    if (it == 0 || it > texture_coords_.size()) {
      throw RuntimeError{
          "OBJ error (line {}): invalid texture coordinates index {}", i, it};
    }
    if (in == 0 || in > normals_.size()) {
      throw RuntimeError{"OBJ error (line {}): invalid normal index {}", i, in};
    }
    face.vertices[j] = vertices_[iv - 1];
    face.texture_coords[j] = texture_coords_[it - 1];
    face.normals[j] = normals_[in - 1];
  }
}

}  // namespace rt
