#pragma once

#include <filesystem>
#include <memory>

#include <rt/common/image.hh>

namespace rt {

class ImageLoader {
 public:
  explicit ImageLoader(const std::filesystem::path& path);
  ~ImageLoader() noexcept;

  std::unique_ptr<Image> Load();

 private:
  struct Implementation;
  std::unique_ptr<Implementation> impl_;
};

}  // namespace rt
