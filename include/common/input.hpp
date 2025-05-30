#ifndef COMMON_INPUT_HPP
#define COMMON_INPUT_HPP
#include <cxxopts.hpp>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace hpn {
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