#ifndef BINARIZE_INPUT_HPP
#define BINARIZE_INPUT_HPP
#include <cxxopts.hpp>
#include <filesystem>

namespace hpn {
struct BinarizeOptions
{
  BinarizeOptions(const std::filesystem::path& inp, const std::filesystem::path& out,
                  int w, int h, int t, bool s);
  std::filesystem::path inputFolder;
  std::filesystem::path outputFile;
  int width;
  int height;
  int threshold;
  bool show;
};

BinarizeOptions getBinOpt(int argc, char* argv[]);
} // namespace hpn
#endif