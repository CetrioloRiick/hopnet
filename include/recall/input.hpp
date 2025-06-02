#ifndef INPUT_RECALL_HPP
#define INPUT_RECALL_HPP
#include <cxxopts.hpp>
#include <cstddef>
#include <filesystem>

namespace hpn {
struct RecallOptions
{
  RecallOptions(const std::filesystem::path& weiF, const std::filesystem::path& inpF,
                int w, int h, bool monF, double noiP);

  std::filesystem::path weightsFile;
  std::filesystem::path inputFile;
  int width;
  int height;
  bool monitorFlag;
  double noiseProbability;

  size_t neuronCount();
};

RecallOptions getRecallOpt(int argc, char* argv[]);
} // namespace hpn
#endif