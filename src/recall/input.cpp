#include "recall/input.hpp"
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <string>
// #include <type_traits>
// #include <concepts>

namespace hpn {
RecallOptions::RecallOptions(const std::filesystem::path& wei,
                             const std::filesystem::path& inp, size_t n)
    : weightsFile(wei)
    , inputFile(inp)
    , patternSize(n)
{
  if (!std::filesystem::exists(inputFile)
      || !std::filesystem::is_regular_file(inputFile)) {
    throw std::invalid_argument("inputFile not valid");
  }
}

RecallOptions getRecallOpt(int argc, char* argv[])
{
  cxxopts::Options options(
      "recall",
      "Run the recall phase of a Hopfield neural network: load weights, "
      "correct a corrupted pattern, and observe convergence.");

  options.add_options()(
      "w,weights", "Path to the weight matrix file",
      cxxopts::value<std::string>()->default_value("hopfield-weights.txt"))(
      "i,input", "Corrupted input pattern to recall (as -1/+1 values)",
      cxxopts::value<std::string>()->default_value("pattern.txt"))(
      "p,pattern-size", "...", cxxopts::value<size_t>())("h,help",
                                                         "Print help");

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  return {result["weights"].as<std::string>(),
          result["input"].as<std::string>(),
          result["pattern-size"].as<size_t>()};
}
} // namespace hpn