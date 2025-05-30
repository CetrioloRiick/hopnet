#include "recall/neural_network.hpp"
#include "common/weight_matrix.hpp"
#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace hpn {
size_t NeuralNetwork::size_{0};

NeuralNetwork::NeuralNetwork(const std::string& buffer)
{
  if (size_ == 0) {
    throw std::runtime_error("Set size before creating instances");
  }
  std::istringstream ss(buffer);
  // Legge una stringa come fosse l'input di un std::cin

  std::generate_n(std::back_inserter(pixelsValue_), size_, [&]() {
    int px;
    ss >> px;
    if (px != -1 && px != +1) {
      throw std::invalid_argument("Invalid value in pattern: must be -1 or +1");
    }
    if (!ss) {
      throw std::invalid_argument("buffer troppo non valido/troppo corto");
    }
    return px;
  });
  assert(pixelsValue_.size() == size_);
}

NeuralNetwork::NeuralNetwork(const std::vector<int>& pV)
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
}

void NeuralNetwork::setSize(size_t n)
{
  if (size_ != 0) {
    throw std::runtime_error("Size already set");
  }
  size_ = n;
  if (size_ < 1) {
    throw std::invalid_argument("pixelCount must be greater than 1");
  }
}

std::vector<int> NeuralNetwork::getNeuronsValue() const
{
  return pixelsValue_;
}

int& NeuralNetwork::operator[](size_t index)
{
  return pixelsValue_[index];
}

/* bool NeuralNetwork::operator!=(const hpn::NeuralNetwork& other) const
{
  if (pixelsValue_ != other.getNeuronsValue()) {
    return true;
  } else {
    return false;
  }
} */
/* NeuralNetwork NeuralNetwork::operator=(const NeuralNetwork& p){

} */

size_t NeuralNetwork::size() const
{
  return size_;
}
std::vector<NeuralNetwork> loadNeuralNetworks(const std::filesystem::path& path)
{
  std::ifstream is{path};
  if (!is) {
    throw std::runtime_error("Cannot open input file");
  }
  std::vector<NeuralNetwork> patterns;
  std::string line;
  while (std::getline(is, line)) {
    patterns.push_back({line});
  }
  return patterns;
}

bool NeuralNetwork::updateState(const WeightMatrix& mat)
{
  oldNeurons_ = pixelsValue_;
  auto sign = [](float n) { return (n > 0) - (n < 0); };
  std::vector<int> result(size_, 0.f);

  for (size_t i{0}; i < size_; ++i) {
    float sum{0.f};
    for (size_t j{0}; j < size_; ++j) {
      sum += mat[i, j] * static_cast<float>(pixelsValue_[j]);
      //std::cout << "quici arrivodio porco!\n";

      /* std::cout << "(*this)[i, j]: " << mat[i, j] << "   ";
      std::cout << "static_cast<float>(pat[j]) " << static_cast<float>(pixelsValue_[j])
                << "   ";

      std::cout << "sum: " << sum << '\n'; */
    }
    pixelsValue_[i] = sign(sum);
    //std::cout << "sign(sum): " << sign(sum) << "\n\n";
  }
  if (oldNeurons_==pixelsValue_) {
    return false;
  }
  return true;
}
void NeuralNetwork::minimizeState(const WeightMatrix& mat, bool monitor)
{
  if (mat.getN() != size_) {
    throw std::invalid_argument("WeightMatrix dimension must match NeuralNetwork size");
  }
  while (updateState(mat)) {
    if (monitor) {
      std::cout << "ENERGIA\n";
    }
  }
}

} // namespace hpn