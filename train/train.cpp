#include "train.hpp"
#include "../common/weight_matrix.hpp"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace hpn {
Pattern::Pattern(const std::string& buffer)
{
  std::istringstream ss(buffer);
  // Legge una stringa come fosse l'input di un std::cin

  std::generate_n(std::back_inserter(pixelsValue_), pixelCount_, [&]() {
    int px;
    ss >> px;
    if (px != -1 && px != +1) {
      throw std::invalid_argument("Invalid value in pattern: must be -1 or +1");
    }
    return px;
  });
}

std::vector<int> Pattern::getPixelsValue() const
{
  return pixelsValue_;
}

int Pattern::operator[](size_t index) const
{
  return pixelsValue_[index];
}
int Pattern::operator[](int index) const
{
  return pixelsValue_[static_cast<size_t>(index)];
}

std::vector<Pattern> loadPatterns(const std::filesystem::path& path)
{
  std::ifstream is{path};
  if (!is) {
    throw std::runtime_error("Cannot open input file");
  }
  std::vector<Pattern> patterns;
  std::string line;
  while (std::getline(is, line)) {
    patterns.push_back({line});
  }
  return patterns;
}
} // namespace hpn