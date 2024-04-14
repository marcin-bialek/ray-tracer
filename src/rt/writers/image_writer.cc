#include "image_writer.hh"

#include <rt/common/exception.hh>

namespace rt {

std::vector<details::ImageWriterImplDesc> ImageWriter::impls_{};

ImageWriter::ImageWriter(const std::filesystem::path& path, std::size_t width,
                         std::size_t height, std::size_t frames,
                         std::size_t fps) {
  for (auto& impl : impls_) {
    if (impl.supports(path)) {
      impl_ = impl.constructor(path, width, height, frames, fps);
      break;
    }
  }
  if (!impl_) {
    throw RuntimeError{"error writing {}: unsupported format", path.string()};
  }
}

void ImageWriter::Write(const Image& image, std::size_t frame) {
  impl_->Write(image, frame);
}

std::vector<std::string> ImageWriter::Formats() noexcept {
  std::vector<std::string> formats;
  for (auto impl : impls_) {
    auto f = impl.formats();
    formats.insert(formats.end(), f.begin(), f.end());
  }
  return formats;
}

}  // namespace rt
