#ifndef INPUT_RECALL_HPP
#define INPUT_RECALL_HPP
#include <cxxopts.hpp>
#include <filesystem>
#include <fstream>

namespace hpn {
struct RecallOptions
{
  RecallOptions(const std::filesystem::path& wei, const std::filesystem::path& inp,
                const std::filesystem::path& out, int w, int h, bool mon, double noi);

  std::filesystem::path weightsFile;
  std::filesystem::path inputFile;
  std::filesystem::path outputFile;
  int width;
  int height;
  bool monitorFlag;
  double noiseProbability;

  size_t neuronCount();
};

RecallOptions getRecallOpt(int argc, char* argv[]);

template<typename T>
  requires std::is_arithmetic_v<T>
std::vector<T> loadVector(const std::filesystem::path& path)
{
  std::vector<T> values;
  std::ifstream is{path};
  if (!is) {
    throw std::runtime_error("Cannot open input file: " + path.string());
  }

  std::string line;
  while (std::getline(is, line)) {
    std::istringstream iss(line);
    T number;
    while (iss >> number) {
      values.push_back(number);
    }
  }

  return values;
}
} // namespace hpn
#endif