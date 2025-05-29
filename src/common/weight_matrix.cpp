#include "common/weight_matrix.hpp"
#include <cassert>
#include <cstddef>
#include <stdexcept>

namespace hpn {
WeightMatrix::WeightMatrix(size_t N)
    : N_(N)
{
  if (N_ < 1) {
    throw std::invalid_argument("N must be greater than 1");
  }
  weights_.resize(effectiveSize());
}

std::vector<float> WeightMatrix::getWeights() const
{
  return weights_;
}
float WeightMatrix::operator[](size_t i, size_t j) const
{
  if (i >= N_ || j >= N_) {
    throw std::invalid_argument("Index of WeightMatrix out of order");
  }
  if (i == j) {
    return 0;
  }

  auto calcIndex = [&](size_t I, size_t J) {
    return I * N_ + (J - I - 1) - I * (I + 1) / 2;
  };

  if (i < j) {
    assert(calcIndex(i, j) <= effectiveSize());
    return weights_[calcIndex(i, j)];
  } else {
    assert(calcIndex(j, i) <= effectiveSize());
    return weights_[calcIndex(j, i)];
  }
}
size_t WeightMatrix::getN() const{
  return N_;
}
size_t WeightMatrix::effectiveSize() const
{
  return ((N_ * N_) - N_) / 2;
}
} // namespace hpn
