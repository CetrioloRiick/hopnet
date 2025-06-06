#include "binarize/utils.hpp"
#include <cxxopts.hpp>
#include <cctype>
#include <filesystem>
#include <string>
#include <unordered_set>

namespace hpn {
bool isAcceptedImage(const std::filesystem::directory_entry& entry)
{
  static const std::unordered_set<std::string> acceptedExt = {
      ".png", ".jpg", ".jpeg", ".bmp", ".tiff", ".tif", ".webp"};
  if (!entry.is_regular_file()) {
    return false;
  }
  std::string ext = entry.path().extension().string();
  return acceptedExt.contains(ext);
}
} // namespace hpn
