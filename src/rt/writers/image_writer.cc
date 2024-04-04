#include "image_writer.hh"

#include <OpenImageIO/imageio.h>

#include <rt/common/exception.hh>

namespace rt {

struct ImageWriter::Implementation {
  std::filesystem::path path;
  OIIO::ImageOutput::unique_ptr file;
  std::vector<OIIO::ImageSpec> specs;
};

ImageWriter::ImageWriter(const std::filesystem::path& path, std::size_t width,
                         std::size_t height, std::size_t frames,
                         std::size_t fps)
    : impl_{std::make_unique<Implementation>()} {
  impl_->path = path;
  impl_->file = OIIO::ImageOutput::create(path.string());
  if (!impl_->file) {
    throw RuntimeError{"error writing {}: {}", path.string(), OIIO::geterror()};
  }
  if (frames > 1 && !impl_->file->supports("multiimage")) {
    throw RuntimeError{"error writing {}: format does not support multi-image",
                       impl_->path.string()};
  }
  for (std::size_t i = 0; i < frames; ++i) {
    impl_->specs.emplace_back(static_cast<int>(width), static_cast<int>(height),
                              4, OIIO::TypeDesc::UINT8);
  }
  if (!impl_->file->open(path, frames, impl_->specs.data())) {
    throw RuntimeError{"error writing {}: {}", path.string(), OIIO::geterror()};
  }
}

ImageWriter::~ImageWriter() noexcept = default;

void ImageWriter::Write(const Image& image, std::size_t frame) {
  if (frame > 0 && !impl_->file->open(impl_->path, impl_->specs[frame],
                                      OIIO::ImageOutput::AppendSubimage)) {
    throw RuntimeError{"error writing {}: {}", impl_->path.string(),
                       OIIO::geterror()};
  }
  auto buffer = image.ToRGBABuffer();
  if (!impl_->file->write_image(OIIO::TypeDesc::DOUBLE, buffer.data())) {
    throw RuntimeError{"error writing {}: {}", impl_->path.string(),
                       OIIO::geterror()};
  }
}

}  // namespace rt
