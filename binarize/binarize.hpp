#ifndef BINARIZE_HPP
#define BINARIZE_HPP

#include <filesystem>
namespace hpn {
struct BinarizeOptions
{
  BinarizeOptions(std::filesystem::path inputFolder, int width, int height, int threshold);
  std::filesystem::path inputFolder;
  int width;
  int height;
  int threshold;
};
} // namespace hpn

#endif