#include "weight_matrix.hpp"
#include <cstddef>
#include <stdexcept>

namespace hpn {
WeightMatrix::WeightMatrix(size_t N)
    : N_(N)
    , effectiveEl_(((N_ * N_) - N_) / 2)
{
  if (N_ < 1) {
    throw std::invalid_argument("N must be greater than 1");
  }
  weights_.resize(static_cast<size_t>(effectiveEl_));
}

std::vector<float> WeightMatrix::getWeights() const
{
  return weights_;
}
float WeightMatrix::operator[](size_t i, size_t j)
{
  if (i >= N_ || j >= N_) {
    throw std::invalid_argument("Index of WeightMatrix out of order");
  }
  if (i == j) {
    return 0;
  }
  auto calcIndex = [&](size_t indexI, size_t indexJ) {
    return indexI * N_ + indexJ;
  };
  if (i < j) {
    return weights_[calcIndex(i, j)];
  } else {
    return weights_[calcIndex(j, i)];
  }
}
} // namespace hpn
