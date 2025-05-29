#include "train/input.hpp"
#include <iostream>

namespace hpn {
TrainOptions::TrainOptions(const std::filesystem::path& inp,
                           const std::filesystem::path& out, size_t n)
    : inputFile(inp)
    , outputFile(out)
    , patternSize(n)
{
  if (!std::filesystem::exists(inputFile)
      || !std::filesystem::is_regular_file(inputFile)) {
    throw std::invalid_argument("inputFile not valid");
  }
  if (n < 1) {
    throw std::invalid_argument("patternSize must be greater than 1");
  }
}

TrainOptions getTrainOpt(int argc, char* argv[])
{
  cxxopts::Options options("train",
                           "Train a Hopfield neural network from binary image "
                           "patterns and save the weight matrix.");

  options.add_options()(
      "i,input", "Input file path",
      cxxopts::value<std::string>()->default_value("binarized-images.txt"))(
      "p,pattern-size", "...", cxxopts::value<size_t>())(
      "o,output", "Output file path for weight matrix",
      cxxopts::value<std::string>()->default_value("hopfield-weights.txt"))(
      "h,help", "Print help");

  auto result = options.parse(argc, argv);

  if (result.count("help") || !result.count("pattern-size")) {
    // Valuta la gestione dei 2 casi separati una con exception l'altra
    std::cout << options.help() << std::endl;
    exit(0);
  }

  return {result["input"].as<std::string>(), result["output"].as<std::string>(),
          result["pattern-size"].as<size_t>()};
}
} // namespace hpn
