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
size_t Pattern::size_{1};

Pattern::Pattern(const std::string& buffer)
{
  std::istringstream ss(buffer);
  // Legge una stringa come fosse l'input di un std::cin

  std::generate_n(std::back_inserter(pixelsValue_), size_, [&]() {
    int px;
    ss >> px;
    if (px != -1 && px != +1) {
      throw std::invalid_argument("Invalid value in pattern: must be -1 or +1");
    }
    return px;
  });
}
void Pattern::setSize(size_t n)
{
  size_ = n;
  if (size_ < 1) {
    throw std::invalid_argument("pixelCount must be greater than 1");
  }
}

std::vector<int> Pattern::getPixelsValue() const
{
  return pixelsValue_;
}

int Pattern::operator[](size_t index) const
{
  return pixelsValue_[index];
}

size_t Pattern::size() const
{
  return size_;
}
} // namespace hpn