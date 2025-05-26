#ifndef INPUT_HPP
#define INPUT_HPP
#include <cxxopts.hpp>
#include <cstddef>
#include <filesystem>
#include <vector>

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
  TrainOptions(const std::filesystem::path& inp,
               const std::filesystem::path& out, int n);
  std::filesystem::path inputFile;
  std::filesystem::path outputFile;
  size_t patternSize;
};

TrainOptions getTrainOpt(int argc, char* argv[]);

struct RecallOptions
{
  RecallOptions(const std::filesystem::path& wei,
                const std::filesystem::path& inp);
  std::filesystem::path weightsFile;
  std::filesystem::path inputFile;
};

RecallOptions getRecallOpt(int argc, char* argv[]);

std::vector<float> loadVector(const std::filesystem::path& path);
} // namespace hpn
#endif