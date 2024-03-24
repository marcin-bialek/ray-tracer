#pragma once

#include <filesystem>
#include <memory>

#include <rt/common/image.hh>

namespace rt {

class ImagerWriter {
 public:
  struct Config {
    std::filesystem::path path;
    bool gamma_correction = false;
  };

  explicit ImagerWriter(const Config& config);

  ~ImagerWriter() noexcept;

  void Write(const Image& image);

 private:
  Config config_;
  struct Implementation;
  std::unique_ptr<Implementation> impl_;
};

}  // namespace rt
