#ifndef INPUT_RECALL_HPP
#define INPUT_RECALL_HPP
#include <cxxopts.hpp>
#include <filesystem>

namespace hpn {
struct RecallOptions
{
  RecallOptions(const std::filesystem::path& weiF, const std::filesystem::path& inpF,
                size_t patS, bool monF, float noiP);
  std::filesystem::path weightsFile;
  std::filesystem::path inputFile;
  size_t patternSize;
  bool monitorFlag;
  float noiseProbability;
};

RecallOptions getRecallOpt(int argc, char* argv[]);
} // namespace hpn
#endif