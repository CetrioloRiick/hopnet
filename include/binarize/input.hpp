#ifndef INPUT_BINARIZE_HPP
#define INPUT_BINARIZE_HPP
#include <cxxopts.hpp>
#include <filesystem>

namespace hpn {
struct BinarizeOptions
{
  BinarizeOptions(const std::filesystem::path& inp, int w, int h, int t, bool s);
  std::filesystem::path inputFolder;
  int width;
  int height;
  int threshold;
  bool show;
};

BinarizeOptions getBinOpt(int argc, char* argv[]);
} // namespace hpn
#endif