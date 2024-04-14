#pragma once

#include <vector>

#include "image_writer_implementation.hh"

namespace rt {

class ImageWriter {
 public:
  explicit ImageWriter(const std::filesystem::path& path, std::size_t width,
                       std::size_t height, std::size_t frames = 1,
                       std::size_t fps = 30);

  void Write(const Image& image, std::size_t frame = 0);

  template <details::ImageWriterImplementationC Impl>
  static void Register() {
    impls_.push_back(details::ImageWriterImplDesc::Create<Impl>());
  }

  static std::vector<std::string> Formats() noexcept;

 private:
  static std::vector<details::ImageWriterImplDesc> impls_;
  std::unique_ptr<details::ImageWriterImplementation> impl_;
};

}  // namespace rt
