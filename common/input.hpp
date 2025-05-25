#ifndef INPUT_HPP
#define INPUT_HPP
#include <cxxopts.hpp>
#include <filesystem>

namespace hpn {
struct BinarizeOptions
{
  BinarizeOptions(const std::filesystem::path& inp, int w, int h, int t);
  std::filesystem::path inputFolder;
  int width;
  int height;
  int threshold;
};

BinarizeOptions getBinOpt(int argc, char* argv[]);

struct TrainOptions
{
  TrainOptions(const std::filesystem::path& inp);
  std::filesystem::path inputFile;
};

TrainOptions getTrainOpt(int argc, char* argv[]);
} // namespace hpn
#endif