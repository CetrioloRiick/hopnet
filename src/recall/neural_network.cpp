#include "recall/neural_network.hpp"
#include "common/weight_matrix.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <random>
#include <stdexcept>

namespace hpn {
size_t NeuralNetwork::size_{0};

NeuralNetwork::NeuralNetwork(const std::vector<int>& n)
    : neurons_(n)
{
  if (size_ == 0) {
    throw std::runtime_error("Set size before creating instances");
  }

  if (neurons_.size() != size_) {
    throw std::invalid_argument("Neurons must have size " + std::to_string(size_));
  }

  if (std::any_of(neurons_.begin(), neurons_.end(),
                  [](int val) { return val != -1 && val != 0 && val != 1; })) {
    throw std::invalid_argument("Neurons must contain only -1, 0, or 1 values");
  }
}

void NeuralNetwork::setSize(size_t n)
{
  if (size_ != 0) {
    throw std::runtime_error("Size already set");
  }
  size_ = n;
}

std::vector<int> NeuralNetwork::getNeuronsValue() const
{
  return neurons_;
}

int& NeuralNetwork::operator[](size_t index)
{
  return neurons_[index];
}

/* bool NeuralNetwork::operator!=(const hpn::NeuralNetwork& other) const
{
  if (neurons_ != other.getNeuronsValue()) {
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

bool NeuralNetwork::updateState(const WeightMatrix& mat)
{
  auto sign = [](double n) { return (n > 0) - (n < 0); };
  std::vector<int> result(size_, 0.f);

  for (size_t i{0}; i < size_; ++i) {
    double sum{0.f};
    for (size_t j{0}; j < size_; ++j) {
      sum += mat[i, j] * static_cast<double>(neurons_[j]);
      // std::cout << "quici arrivodio porco!\n";

      /* std::cout << "(*this)[i, j]: " << mat[i, j] << "   ";
      std::cout << "static_cast<double>(pat[j]) " << static_cast<double>(neurons_[j])
                << "   ";

      std::cout << "sum: " << sum << '\n'; */
    }
    neurons_[i] = sign(sum);
    // std::cout << "sign(sum): " << sign(sum) << "\n\n";
  }
  if (oldNeurons_ == neurons_) {
    return false;
  }
  return true;
}
void NeuralNetwork::minimizeState(const WeightMatrix& mat, bool monitor)
{
  if (mat.getN() != size_) {
    throw std::invalid_argument("WeightMatrix dimension must match NeuralNetwork size");
  }
  do {
    oldNeurons_ = neurons_;
    updateState(mat);
    if (monitor) {
      std::cout << "Energy: " << getEnergy(mat) << std::endl;
    }
  } while (oldNeurons_ != neurons_);
}
void NeuralNetwork::randomize(double prob)
{
  if (prob > 1 || prob < 0) {
    throw std::invalid_argument("Probability must be between 0 and 1");
  }
  if (prob == 0) {
    return;
  }
  std::default_random_engine eng;
  std::uniform_real_distribution<> dis(0.0, 1.0);

  std::transform(neurons_.begin(), neurons_.end(), neurons_.begin(),
                 [&](int val) { return (dis(eng) < prob) ? (val == 1 ? -1 : 1) : val; });
}

double NeuralNetwork::getEnergy(const WeightMatrix& wm) const
{
  double sum{0.f};
  for (size_t i{0}; i != size_; ++i) {
    for (size_t j{0}; j != size_; ++j) {
      sum += wm[i, j] * static_cast<double>(neurons_[i] * neurons_[j]);
    }
  }
  return -sum / 2;
}

} // namespace hpn