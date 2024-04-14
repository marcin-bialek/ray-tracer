#pragma once

#include <filesystem>
#include <memory>
#include <vector>

#include <rt/common/image.hh>

namespace rt::details {

struct ImageWriterImplementation {
  explicit ImageWriterImplementation() noexcept = default;
  ImageWriterImplementation(const ImageWriterImplementation&) = delete;
  ImageWriterImplementation(ImageWriterImplementation&&) = delete;
  ImageWriterImplementation& operator=(const ImageWriterImplementation&) =
      delete;
  ImageWriterImplementation& operator=(ImageWriterImplementation&&) = delete;
  virtual ~ImageWriterImplementation() noexcept = default;
  virtual void Write(const Image& image, std::size_t frame) = 0;
};

template <typename Tp>
concept ImageWriterImplementationC =
    std::is_base_of_v<ImageWriterImplementation, Tp> &&
    std::is_constructible_v<Tp, const std::filesystem::path&, std::size_t,
                            std::size_t, std::size_t, std::size_t> &&
    requires(Tp impl) {
      { Tp::Formats() } -> std::convertible_to<std::vector<std::string>>;
      {
        Tp::Supports(std::declval<std::filesystem::path>())
      } -> std::convertible_to<bool>;
    };

struct ImageWriterImplDesc {
  using Constructor = std::function<std::unique_ptr<ImageWriterImplementation>(
      const std::filesystem::path&, std::size_t, std::size_t, std::size_t,
      std::size_t)>;
  using Formats = std::function<std::vector<std::string>()>;
  using Supports = std::function<bool(const std::filesystem::path&)>;

  Constructor constructor;
  Formats formats;
  Supports supports;

  template <ImageWriterImplementationC Impl>
  static ImageWriterImplDesc Create() noexcept {
    ImageWriterImplDesc desc{};
    desc.constructor = [](const std::filesystem::path& path, std::size_t width,
                          std::size_t height, std::size_t frames,
                          std::size_t fps) {
      return std::make_unique<Impl>(path, width, height, frames, fps);
    };
    desc.formats = Impl::Formats;
    desc.supports = Impl::Supports;
    return desc;
  }
};

}  // namespace rt::details
