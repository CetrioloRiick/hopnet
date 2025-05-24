#ifndef BINARIZE_HPP
#define BINARIZE_HPP

#include <filesystem>
namespace hpn {
struct BinarizeOptions
{
  BinarizeOptions(std::filesystem::path inp, int w, int h, int t);
  std::filesystem::path inputFolder;
  int width;
  int height;
  int threshold;
};
} // namespace hpn

#endif