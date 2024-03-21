#pragma once

#include <filesystem>
#include <memory>

#include <rt/common/image.hh>

namespace rt {

class ImagerWriter {
 public:
  explicit ImagerWriter(const std::filesystem::path& path);

  ~ImagerWriter() noexcept;

  void Write(const Image& image);

 private:
  struct Implementation;
  std::unique_ptr<Implementation> impl_;
};

}  // namespace rt
