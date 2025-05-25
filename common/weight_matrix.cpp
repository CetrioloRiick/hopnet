#include "weight_matrix.hpp"

namespace hpn {
WeightMatrix::WeightMatrix(int N)
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
} // namespace hpn
