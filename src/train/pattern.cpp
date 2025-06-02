#include "train/pattern.hpp"
#include "common/input.hpp"
#include "common/weight_matrix.hpp"
#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>

namespace hpn {
size_t Pattern::size_{0};

Pattern::Pattern(const std::string& buffer)
{
  if (size_ == 0) {
    throw std::runtime_error("Set size before creating instances");
  }
  std::istringstream ss(buffer);
  // Legge una stringa come fosse l'input di un std::cin
  std::generate_n(std::back_inserter(pixelsValue_), size_, [&]() {
    int px;
    ss >> px;
    if (!ss) {
      throw std::invalid_argument("buffer troppo non valido/troppo corto");
    }
    if (px != -1 && px != +1) {
      throw std::invalid_argument("Invalid value in pattern: must be -1 or +1");
    }
    return px;
  });
  assert(pixelsValue_.size() == size_);
}

/* Pattern::Pattern(const std::vector<int>& pV)
    : pixelsValue_(pV)
{
  if (size_ == 0) {
    throw std::runtime_error("Set size before creating instances");
  }

  if (pixelsValue_.size() != size_) {
    throw std::invalid_argument("pixelValue must have size " + std::to_string(size_));
  }

  if (std::any_of(pixelsValue_.begin(), pixelsValue_.end(),
                  [](int val) { return val != -1 && val != 0 && val != 1; })) {
    throw std::invalid_argument("pixelValue must contain only -1, 0, or 1 values");
  }
} */

void Pattern::setSize(size_t n)
{
  if (size_ != 0) {
    throw std::runtime_error("Size already set");
  }
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

bool Pattern::operator!=(const hpn::Pattern& other) const
{
  if (pixelsValue_ != other.getPixelsValue()) {
    return true;
  } else {
    return false;
  }
}
/* Pattern Pattern::operator=(const Pattern& p){

} */

size_t Pattern::size() const
{
  return size_;
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