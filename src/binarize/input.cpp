#include "binarize/input.hpp"
#include <iostream>
#include <string>

namespace hpn {
BinarizeOptions::BinarizeOptions(const std::filesystem::path& inp,
                                 const std::filesystem::path& out, int w, int h, int t,
                                 bool s)
    : inputFolder(inp)
    , outputFile(out)
    , width(w)
    , height(h)
    , threshold(t)
    , show(s)
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
  cxxopts::Options options("binarize",
                           "Convert all images in a folder to binary format (-1, +1)");

  options.add_options()("i,input", "Input folder path", cxxopts::value<std::string>())(
      "o,output", "Output file path",
      cxxopts::value<std::string>()->default_value("binarized-images.txt"))(
      "W,width", "Width to resize each image to before binarization",
      cxxopts::value<int>()->default_value("50"))(
      "H,height", "Height to resize each image to before binarization",
      cxxopts::value<int>()->default_value("50"))(
      "t,threshold", "Threshold for binarization (0-255)",
      cxxopts::value<int>()->default_value("127"))(
      "s,show", "Save each binarized image during processing",
      cxxopts::value<bool>()->default_value("false"))("help", "Print help");

  auto result = options.parse(argc, argv);

  if (result.count("help") || !result.count("input")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  return {result["input"].as<std::string>(), result["output"].as<std::string>(),
          result["width"].as<int>(),         result["height"].as<int>(),
          result["threshold"].as<int>(),     result["show"].as<bool>()};
}
} // namespace hpn