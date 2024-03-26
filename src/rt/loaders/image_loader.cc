#include "image_loader.hh"

#include <fstream>

#include <spng/spng.h>

#include <rt/common/exception.hh>

namespace rt {

struct ImagerLoader::Implementation {
  spng_ctx* ctx;
  std::ifstream file;
  std::filesystem::path path;
};

ImagerLoader::ImagerLoader(const std::filesystem::path& path)
    : impl_{std::make_unique<Implementation>()} {
  impl_->ctx = spng_ctx_new(0);
  impl_->file.open(path, std::ios::binary);
  impl_->path = path;
  if (!impl_->file.good()) {
    throw RuntimeError{"could not open {}", path.c_str()};
  }
}

ImagerLoader::~ImagerLoader() noexcept {
  if (impl_->ctx) {
    spng_ctx_free(impl_->ctx);
  }
}

std::unique_ptr<Image> ImagerLoader::Load() {
  impl_->file.unsetf(std::ios::skipws);
  impl_->file.seekg(0, impl_->file.end);
  auto file_size = impl_->file.tellg();
  impl_->file.seekg(0, impl_->file.beg);
  std::vector<uint8_t> file_buffer(file_size);
  file_buffer.insert(file_buffer.begin(),
                     std::istream_iterator<uint8_t>{impl_->file},
                     std::istream_iterator<uint8_t>{});
  spng_set_png_buffer(impl_->ctx, file_buffer.data(), file_buffer.size());
  spng_ihdr ihdr{};
  auto err = spng_get_ihdr(impl_->ctx, &ihdr);
  if (err) {
    throw RuntimeError{"error loading {}: {}", impl_->path.c_str(),
                       spng_strerror(err)};
  }
  std::vector<uint8_t> image_buffer(ihdr.width * ihdr.height * 3);
  err = spng_decode_image(impl_->ctx, image_buffer.data(), image_buffer.size(),
                          SPNG_FMT_RGB8, 0);
  if (err) {
    throw RuntimeError{"error loading {}: {}", impl_->path.c_str(),
                       spng_strerror(err)};
  }
  auto image = std::make_unique<Image>(ihdr.width, ihdr.height);
  auto p = image_buffer.begin();
  for (std::size_t y = 0; y < image->height(); ++y) {
    for (std::size_t x = 0; x < image->width(); ++x) {
      (*image)[{x, y}] = {
          static_cast<double>(*(p++)) / 255.0,
          static_cast<double>(*(p++)) / 255.0,
          static_cast<double>(*(p++)) / 255.0,
      };
    }
  }
  return std::move(image);
}

}  // namespace rt
