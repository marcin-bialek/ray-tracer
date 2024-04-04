#include "image_writer.hh"

#include <OpenImageIO/imageio.h>
#include <gif/gif.h>

#include <rt/common/exception.hh>

namespace rt {

class ImageWriter::Implementation {
 public:
  virtual ~Implementation() noexcept = default;
  virtual void Write(const Image& image, std::size_t frame) = 0;
};

class ImageWriter::OIIOImplementation : public Implementation {
 public:
  explicit OIIOImplementation(const std::filesystem::path& path,
                              std::size_t width, std::size_t height,
                              std::size_t frames, std::size_t fps)
      : path_{path}, file_{OIIO::ImageOutput::create(path_.string())} {
    if (!file_) {
      throw RuntimeError{"error writing {}: {}", path_.string(),
                         OIIO::geterror()};
    }
    if (frames > 1 && !file_->supports("multiimage")) {
      throw RuntimeError{
          "error writing {}: format does not support multi-image",
          path_.string()};
    }
    specs_.reserve(frames);
    for (std::size_t i = 0; i < frames; ++i) {
      specs_.emplace_back(static_cast<int>(width), static_cast<int>(height), 4,
                          OIIO::TypeDesc::UINT8);
    }
    if (!file_->open(path_, frames, specs_.data())) {
      throw RuntimeError{"error writing {}: {}", path_.string(),
                         OIIO::geterror()};
    }
  }

  void Write(const Image& image, std::size_t frame) override {
    if (frame > 0 &&
        !file_->open(path_, specs_[frame], OIIO::ImageOutput::AppendSubimage)) {
      throw RuntimeError{"error writing {}: {}", path_.string(),
                         OIIO::geterror()};
    }
    auto buffer = image.ToRGBABuffer();
    if (!file_->write_image(OIIO::TypeDesc::UINT8, buffer.data())) {
      throw RuntimeError{"error writing {}: {}", path_.string(),
                         OIIO::geterror()};
    }
  }

 private:
  std::filesystem::path path_;
  OIIO::ImageOutput::unique_ptr file_;
  std::vector<OIIO::ImageSpec> specs_;
};

class ImageWriter::GifImplementation : public Implementation {
 public:
  explicit GifImplementation(const std::filesystem::path& path,
                             std::size_t width, std::size_t height,
                             std::size_t fps)
      : path_{path}, delay_{100 / fps} {
    if (!GifBegin(&writer_, path.c_str(), width, height, delay_, 8, true)) {
      throw RuntimeError{"error writing {}", path_.string()};
    }
  }

  ~GifImplementation() noexcept {
    GifEnd(&writer_);
  }

  void Write(const Image& image, std::size_t frame) override {
    auto buffer = image.ToRGBABuffer();
    if (!GifWriteFrame(&writer_, buffer.data(), image.width(), image.height(),
                       delay_, 8, true)) {
      throw RuntimeError{"error writing {}", path_.string()};
    }
  }

 private:
  std::filesystem::path path_;
  std::size_t delay_;
  GifWriter writer_;
};

ImageWriter::ImageWriter(const std::filesystem::path& path, std::size_t width,
                         std::size_t height, std::size_t frames,
                         std::size_t fps) {
  if (path.extension() == ".gif") {
    impl_ = std::make_unique<GifImplementation>(path, width, height, fps);
  } else {
    impl_ =
        std::make_unique<OIIOImplementation>(path, width, height, frames, fps);
  }
}

ImageWriter::~ImageWriter() noexcept = default;

void ImageWriter::Write(const Image& image, std::size_t frame) {
  impl_->Write(image, frame);
}

}  // namespace rt
