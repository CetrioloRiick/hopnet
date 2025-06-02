// #include "common/pattern.hpp"
#include "common/weight_matrix.hpp"
#include <stdexcept>
#include <vector>

namespace hpn {
WeightMatrix::WeightMatrix(size_t N, const std::vector<double>& weights)
    : N_(N)
    , effectiveSize_(((N_ * N_) - N_) / 2)
    , weights_(weights)
{
  if (weights.size() != effectiveSize()) {
    throw std::invalid_argument(
        "Weights must have size equal to effectiveSize: [(N * N) - N] / 2");
  }
}
} // namespace hpn