#include <gif/gif.h>

#include <rt/common/exception.hh>

#include "image_writer.hh"

namespace rt::details {

class GifImplementation : public ImageWriterImplementation {
 public:
  explicit GifImplementation(const std::filesystem::path& path,
                             std::size_t width, std::size_t height,
                             std::size_t frames, std::size_t fps)
      : path_{path}, delay_{100 / fps} {
    if (!GifBegin(&writer_, path.c_str(), width, height, delay_, 8, true)) {
      ThrowError();
    }
  }

  ~GifImplementation() noexcept {
    GifEnd(&writer_);
  }

  void Write(const Image& image, std::size_t frame) override {
    auto buffer = image.ToRGBABuffer();
    if (!GifWriteFrame(&writer_, buffer.data(), image.width(), image.height(),
                       delay_, 8, true)) {
      ThrowError();
    }
  }

  static std::vector<std::string> Formats() noexcept {
    return {"gif"};
  }

  static bool Supports(const std::filesystem::path& path) noexcept {
    if (path.has_extension()) {
      auto ext = path.extension().string().substr(1);
      for (auto format : Formats()) {
        if (format == ext) {
          return true;
        }
      }
    }
    return false;
  }

 private:
  std::filesystem::path path_;
  std::size_t delay_;
  GifWriter writer_;

  void ThrowError() {
    throw RuntimeError{"error writing {}", path_.string()};
  }
};

[[gnu::constructor]] static void RegisterGifImplementation() {
  ImageWriter::Register<GifImplementation>();
}

}  // namespace rt::details
