#ifndef INPUT_HPP
#define INPUT_HPP
#include <cxxopts.hpp>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace hpn {
struct BinarizeOptions
{
  BinarizeOptions(const std::filesystem::path& inp, int w, int h, int t);
  std::filesystem::path inputFolder;
  int width;
  int height;
  int threshold;
};

BinarizeOptions getBinOpt(int argc, char* argv[]);

struct TrainOptions
{
  TrainOptions(const std::filesystem::path& inp,
               const std::filesystem::path& out, size_t n);
  std::filesystem::path inputFile;
  std::filesystem::path outputFile;
  size_t patternSize;
};

TrainOptions getTrainOpt(int argc, char* argv[]);

struct RecallOptions
{
  RecallOptions(const std::filesystem::path& wei,
                const std::filesystem::path& inp, size_t n);
  std::filesystem::path weightsFile;
  std::filesystem::path inputFile;
  size_t patternSize;
};

RecallOptions getRecallOpt(int argc, char* argv[]);

int loadInt(const std::filesystem::path& path);

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