#pragma once

#include <filesystem>
#include <memory>
#include <span>

#include <rt/common/image.hh>

namespace rt {

class ImageWriter {
 public:
  explicit ImageWriter(const std::filesystem::path& path, std::size_t width,
                       std::size_t height, std::size_t frames = 1,
                       std::size_t fps = 30);
  ~ImageWriter() noexcept;

  void Write(const Image& image, std::size_t frame = 0);

 private:
  class Implementation;
  class OIIOImplementation;
  class GifImplementation;
  std::unique_ptr<Implementation> impl_;
};

}  // namespace rt
