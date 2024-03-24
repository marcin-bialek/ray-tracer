#include "image_writer.hh"

#include <cmath>
#include <fstream>

#include <spng/spng.h>

#include <rt/common/exception.hh>

namespace rt {

struct ImagerWriter::Implementation {
  spng_ctx* ctx;
  std::ofstream file;
};

ImagerWriter::ImagerWriter(const Config& config)
    : config_{config}, impl_{std::make_unique<Implementation>()} {
  impl_->ctx = spng_ctx_new(SPNG_CTX_ENCODER);
  impl_->file.open(config_.path, std::ios::binary | std::ios::out);
}

ImagerWriter::~ImagerWriter() noexcept {
  if (impl_->ctx) {
    spng_ctx_free(impl_->ctx);
  }
}

void ImagerWriter::Write(const Image& image) {
  auto buffer = image.ToRGBBuffer();
  auto int_buffer = std::vector<uint8_t>(buffer.size());
  if (config_.gamma_correction) {
    for (auto& v : buffer) {
      v = std::sqrt(v);
    }
  }
  std::ranges::transform(buffer, int_buffer.begin(), [](auto v) {
    return static_cast<uint8_t>(v * 255.0);
  });
  spng_ihdr ihdr{};
  ihdr.width = image.width();
  ihdr.height = image.height();
  ihdr.bit_depth = 8;
  ihdr.color_type = SPNG_COLOR_TYPE_TRUECOLOR;
  spng_set_option(impl_->ctx, SPNG_ENCODE_TO_BUFFER, 1);
  spng_set_ihdr(impl_->ctx, &ihdr);
  int err = spng_encode_image(impl_->ctx, int_buffer.data(), int_buffer.size(),
                              SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE);
  if (err) {
    throw RuntimeError{"error encoding image 0: {}", spng_strerror(err)};
  }
  std::size_t size{0};
  auto output = spng_get_png_buffer(impl_->ctx, &size, &err);
  if (err) {
    throw RuntimeError{"error encoding image 1: {}", spng_strerror(err)};
  }
  impl_->file.write(static_cast<char*>(output), size);
  std::free(output);
}

}  // namespace rt
