#include <OpenImageIO/imageio.h>

#include <rt/common/exception.hh>
#include <rt/common/strings.hh>

#include "image_writer.hh"

namespace rt::details {

class OIIOImplementation : public ImageWriterImplementation {
 public:
  OIIOImplementation(const std::filesystem::path& path, std::size_t width,
                     std::size_t height, std::size_t frames, std::size_t fps)
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

  static std::vector<std::string> Formats() noexcept {
    std::vector<std::string> formats;
    auto list = OIIO::get_string_attribute("extension_list");
    for (const auto& part : Split(list, ";")) {
      auto tmp = Split(part, ":");
      auto format = tmp[0];
      auto ext_list = tmp[1];
      if (format == "gif" || format == "null" || format == "ffmpeg") {
        continue;
      }
      auto extensions = Split(ext_list, ",");
      formats.insert(formats.end(), extensions.begin(), extensions.end());
    }
    return formats;
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
  OIIO::ImageOutput::unique_ptr file_;
  std::vector<OIIO::ImageSpec> specs_;
};

[[gnu::constructor]] static void RegisterOIIOImplementation() {
  ImageWriter::Register<OIIOImplementation>();
}

}  // namespace rt::details
