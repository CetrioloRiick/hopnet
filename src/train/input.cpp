#include "train/input.hpp"
#include <iostream>

namespace hpn {
TrainOptions::TrainOptions(const std::filesystem::path& inp,
                           const std::filesystem::path& out, size_t p)
    : inputFile(inp)
    , outputFile(out)
    , patternSize(p)
{
  if (!std::filesystem::exists(inputFile)
      || !std::filesystem::is_regular_file(inputFile)) {
    throw std::invalid_argument("inputFile not valid");
  }
}

TrainOptions getTrainOpt(int argc, char* argv[])
{
  cxxopts::Options options("train", "Train a Hopfield neural network from binary image "
                                    "patterns and save the weight matrix.");

  options.add_options()(
      "i,input", "Input file path",
      cxxopts::value<std::string>()->default_value("binarized-images.txt"))(
      "p,pattern-size", "Size of the pattern (width * height)",
      cxxopts::value<size_t>()->default_value("2500"))(
      "o,output", "Output file path for weight matrix",
      cxxopts::value<std::string>()->default_value("hopfield-weights.txt"))("h,help",
                                                                            "Print help");

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  return {result["input"].as<std::string>(), result["output"].as<std::string>(),
          result["pattern-size"].as<size_t>()};
}
} // namespace hpn
