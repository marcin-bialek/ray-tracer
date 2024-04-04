#include "image_loader.hh"

#include <OpenImageIO/imageio.h>

#include <rt/common/exception.hh>

namespace rt {

struct ImageLoader::Implementation {
  std::filesystem::path path;
  OIIO::ImageInput::unique_ptr file;
};

ImageLoader::ImageLoader(const std::filesystem::path& path)
    : impl_{std::make_unique<Implementation>()} {
  impl_->path = path;
  impl_->file = OIIO::ImageInput::open(path);
  if (!impl_->file) {
    throw RuntimeError{"error opening {}: {}", path.string(), OIIO::geterror()};
  }
}

ImageLoader::~ImageLoader() noexcept = default;

std::unique_ptr<Image> ImageLoader::Load() {
  auto width = impl_->file->spec().width;
  auto height = impl_->file->spec().height;
  auto channels = impl_->file->spec().nchannels;
  std::vector<double> buffer(width * height * 3);
  if (!impl_->file->read_image(0, 0, 0, 3, OIIO::TypeDesc::DOUBLE,
                               buffer.data())) {
    throw RuntimeError{"error opening {}: {}", impl_->path.string(),
                       OIIO::geterror()};
  }
  auto image = std::make_unique<Image>(width, height);
  auto p = buffer.begin();
  for (std::size_t y = 0; y < image->height(); ++y) {
    for (std::size_t x = 0; x < image->width(); ++x) {
      (*image)[{x, y}] = {*(p++), *(p++), *(p++)};
    }
  }
  return std::move(image);
}

}  // namespace rt
