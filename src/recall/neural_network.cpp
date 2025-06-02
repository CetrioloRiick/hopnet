#include "recall/neural_network.hpp"
#include "common/weight_matrix.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <random>
#include <stdexcept>
#include <fstream>

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

size_t NeuralNetwork::size() const
{
  return size_;
}

bool NeuralNetwork::updateState(const WeightMatrix& mat)
{
  oldNeurons_ = neurons_;

  auto sign = [](double n) { return (n > 0) - (n < 0); };

  for (size_t i{0}; i < size_; ++i) {
    double sum{0.f};
    for (size_t j{0}; j < size_; ++j) {
      sum += mat[i, j] * static_cast<double>(neurons_[j]);
    }
    neurons_[i] = sign(sum);
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
    if (monitor) {
      std::cout << "Energy: " << getEnergy(mat) << std::endl;
    }
  } while (updateState(mat));
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

void NeuralNetwork::save(const std::filesystem::path& path) const
{
  std::ofstream fout(path);
  std::for_each(neurons_.begin(), neurons_.end(),
                [&](const double& w) { fout << w << ' '; });
}

} // namespace hpn