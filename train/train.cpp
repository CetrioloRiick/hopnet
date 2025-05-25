#include "train.hpp"
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
WeightMatrix::WeightMatrix(int N)
    : N_(N)
    , effectiveEl_(((N_ * N_) - N_) / 2)
{
  if (N_ < 1) {
    throw std::invalid_argument("N must be greater than 1");
  }
  weights_.resize(static_cast<size_t>(effectiveEl_));
}
void WeightMatrix::hebbRule(const Pattern& image)
{
  int indexI{0};
  int indexJ{1};
  // Indici della matrice
  std::for_each_n(weights_.begin(), effectiveEl_, [&](float& pippo) {
    assert(indexI < indexJ);
    pippo += static_cast<float>(image[indexI] * image[indexJ])
           / static_cast<float>(N_);
    if (indexJ != N_ - 1) {
      indexJ++;
    } else {
      indexI++;
      indexJ = indexI + 1;
    }
  });
}

/* VERSIONE CON ITERATORI
void WeightMatrix::hebbRule(const Pattern& image)
{
  int num{((N_ * N_) - N_) / 2};
  auto pluto    = image.getPixelsValue().begin();
  auto paperino = image.getPixelsValue().begin();
  int index{0};
  int index2{0};
  std::for_each_n(weights_.begin(), num, [&](float& pippo) {
    if (index != index2) {
      pippo +=
          static_cast<float>((*pluto) * (*paperino)) / static_cast<float>(N_);
    }
    if (index2 != N_ - 1) {
      paperino++;
    } else {
      pluto++;
      paperino=image.getPixelsValue().begin();
      paperino+=pluto;
    }

  });
}*/

void WeightMatrix::hebbRule(const std::vector<Pattern>& images)
{
  std::for_each(images.begin(), images.end(),
                [&](const Pattern& pippo) { hebbRule(pippo); });
}

std::vector<float> WeightMatrix::getWeights() const
{
  return weights_;
}

void WeightMatrix::save(const std::filesystem::path& file) const
{
  std::ofstream fout(file);
  std::for_each(weights_.begin(), weights_.end(),
                [&](const float& w) { fout << w << ' '; });
}

} // namespace hpn