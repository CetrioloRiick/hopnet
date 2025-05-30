#ifndef INPUT_RECALL_HPP
#define INPUT_RECALL_HPP
#include <cxxopts.hpp>
#include <filesystem>

namespace hpn {
struct RecallOptions
{
  RecallOptions(const std::filesystem::path& wei, const std::filesystem::path& inp,
                size_t n, bool m);
  std::filesystem::path weightsFile;
  std::filesystem::path inputFile;
  size_t patternSize;
  bool monitorFlag;
};

RecallOptions getRecallOpt(int argc, char* argv[]);
} // namespace hpn
#endif