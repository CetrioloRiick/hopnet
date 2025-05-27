#include "input.hpp"
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <string>
// #include <type_traits>
// #include <concepts>

namespace hpn {
BinarizeOptions::BinarizeOptions(const std::filesystem::path& inp, int w, int h,
                                 int t)
    : inputFolder(inp)
    , width(w)
    , height(h)
    , threshold(t)
{
  if (!std::filesystem::exists(inputFolder)
      || !std::filesystem::is_directory(inputFolder)) {
    throw std::invalid_argument("inputFolder not valid");
  }
  if (width < 1) {
    throw std::invalid_argument("width must be greater than 1");
  }
  if (height < 1) {
    throw std::invalid_argument("height must be greater than 1");
  }
  if (threshold < 0 || threshold > 255) {
    throw std::invalid_argument("threshold must be between 0 and 255");
  }
}

BinarizeOptions getBinOpt(int argc, char* argv[])
{
  cxxopts::Options options(
      "binarize", "Convert all images in a folder to binary format (-1, +1)");

  options.add_options()("i,input", "Input folder path",
                        cxxopts::value<std::string>())(
      "w,width", "Width to resize each image to before binarization",
      cxxopts::value<int>()->default_value("100"))(
      "h,height", "Height to resize each image to before binarization",
      cxxopts::value<int>()->default_value("100"))(
      "t,threshold", "Threshold for binarization (0-255)",
      cxxopts::value<int>()->default_value("127"))("help", "Print help");

  auto result = options.parse(argc, argv);

  if (result.count("help") || !result.count("input")) {
    // Valuta la gestione dei 2 casi separati una con excption l'altra
    std::cout << options.help() << std::endl;
    exit(0);
  }

  return {result["input"].as<std::string>(), result["width"].as<int>(),
          result["height"].as<int>(), result["threshold"].as<int>()};
}

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

int loadInt(const std::filesystem::path& path)
{
  std::ifstream is{path};
  if (!is.is_open()) {
    throw std::runtime_error("Cannot open input file: " + path.string());
  }

  std::string line;
  if (!std::getline(is, line)) {
    throw std::runtime_error("File is empty or unreadable: " + path.string());
  }

  std::istringstream iss(line);
  int result;
  if (!(iss >> result)) {
    throw std::runtime_error("No valid integer found in first line of file: "
                             + path.string());
  }

  return result;
}
} // namespace hpn
