#pragma once

#include <filesystem>
#include <memory>

#include <rt/common/image.hh>

namespace rt {

class ImagerLoader {
 public:
  explicit ImagerLoader(const std::filesystem::path& path);

  ~ImagerLoader() noexcept;

  std::unique_ptr<Image> Load();

 private:
  struct Implementation;
  std::unique_ptr<Implementation> impl_;
};

}  // namespace rt
