#ifndef INPUT_TRAIN_HPP
#define INPUT_TRAIN_HPP
#include <cxxopts.hpp>
#include <filesystem>

namespace hpn {
struct TrainOptions
{
  TrainOptions(const std::filesystem::path& inp,
               const std::filesystem::path& out, size_t p);
  std::filesystem::path inputFile;
  std::filesystem::path outputFile;
  size_t patternSize;
};

TrainOptions getTrainOpt(int argc, char* argv[]);
} // namespace hpn
#endif