#include "recall/input.hpp"
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <string>
// #include <type_traits>
// #include <concepts>

namespace hpn {
RecallOptions::RecallOptions(const std::filesystem::path& weiF,
                             const std::filesystem::path& inpF, size_t patS, bool monF,
                             float noiP)
    : weightsFile(weiF)
    , inputFile(inpF)
    , patternSize(patS)
    , monitorFlag(monF)
    , noiseProbability(noiP)
{
  if (!std::filesystem::exists(inputFile)
      || !std::filesystem::is_regular_file(inputFile)) {
    throw std::invalid_argument("inputFile not valid");
  }
  if (noiseProbability < 0 || noiseProbability > 1) {
    throw std::invalid_argument("Noise probability must be between 0 and 1");
  }
}

RecallOptions getRecallOpt(int argc, char* argv[])
{
  cxxopts::Options options(
      "recall", "Run the recall phase of a Hopfield neural network: load weights, "
                "correct a corrupted pattern, and observe convergence.");

  options.add_options()(
      "w,weights", "Path to the weight matrix file",
      cxxopts::value<std::string>()->default_value("hopfield-weights.txt"))(
      "i,input", "Corrupted input pattern to recall (as -1/+1 values)",
      cxxopts::value<std::string>()->default_value("pattern.txt"))(
      "p,pattern-size", "Size of the pattern (number of neurons)",
      cxxopts::value<size_t>())("m,monitor-process",
                                "Enable monitoring of energy minimization during recall",
                                cxxopts::value<bool>()->default_value("true"))(
      "n,noise-probability",
      "Probability of introducing noise into the input pattern (0 to 1)",
      cxxopts::value<float>()->default_value("0"))("h,help", "Print help");

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  return {result["weights"].as<std::string>(), result["input"].as<std::string>(),
          result["pattern-size"].as<size_t>(), result["monitor-process"].as<bool>(),
          result["noise-probability"].as<float>()};
}
} // namespace hpn