#include "binarize.hpp"
#include "input.hpp"
#include <cxxopts.hpp>
#include <iostream>

namespace hpn {
BinarizeOptions getOpt(int argc, char* argv[])
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
} // namespace hpn
