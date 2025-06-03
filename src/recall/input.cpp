#include "recall/input.hpp"
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <string>

namespace hpn {
RecallOptions::RecallOptions(const std::filesystem::path& wei,
                             const std::filesystem::path& inp,
                             const std::filesystem::path& out, int w, int h, bool mon,
                             double noi)
    : weightsFile(wei)
    , inputFile(inp)
    , outputFile(out)
    , width(w)
    , height(h)
    , monitorFlag(mon)
    , noiseProbability(noi)
{
  if (!std::filesystem::exists(inputFile)
      || !std::filesystem::is_regular_file(inputFile)) {
    throw std::invalid_argument("inputFile not valid");
  }
  if (width < 1) {
    throw std::invalid_argument("width must be greater than 1");
  }
  if (height < 1) {
    throw std::invalid_argument("height must be greater than 1");
  }
  if (noiseProbability < 0 || noiseProbability > 1) {
    throw std::invalid_argument("Noise probability must be between 0 and 1");
  }
}

size_t RecallOptions::neuronCount()
{
  return static_cast<size_t>(width * height);
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
      "o,output", "Output file path",
      cxxopts::value<std::string>()->default_value("corrected-pattern.txt"))(
      "W,width", "Width (in pixels) of the input pattern",
      cxxopts::value<int>()->default_value("50"))(
      "H,height", "Height (in pixels) of the input pattern",
      cxxopts::value<int>()->default_value("50"))(
      "m,monitor-process", "Enable monitoring of energy minimization during recall",
      cxxopts::value<bool>()->default_value("true"))(
      "n,noise-probability",
      "Probability of introducing noise into the input pattern (0 to 1)",
      cxxopts::value<double>()->default_value("0"))("h,help", "Print help");

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  return {result["weights"].as<std::string>(),
          result["input"].as<std::string>(),
          result["output"].as<std::string>(),
          result["width"].as<int>(),
          result["height"].as<int>(),
          result["monitor-process"].as<bool>(),
          result["noise-probability"].as<double>()};
}
} // namespace hpn