#include "recall.hpp"
#include "../common/pattern.hpp"
#include "../common/weight_matrix.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace hpn {
WeightMatrix::WeightMatrix(size_t N, const std::vector<float>& weights)
    : N_(N)
    , weights_(weights)
{
  if (weights.size() != effectiveSize()) {
    throw std::invalid_argument(
        "Weights must have size equal to effectiveSize: [(N * N) - N] / 2");
  }

  /* if (std::any_of(weights.begin(), weights.end(),
                  [](const float val) { return val > 1; })) {

  } */
}
/* std::vector<float> WeightMatrix::operator*(const std::vector<float>& vec)
{
  std::vector<float> result(N_, 0.f);

  for (size_t i{0}; i < N_; ++i) {
    float sum{0.f};
    for (size_t j{0}; j < N_; ++j) {
      sum += (*this)[i, j] * vec[j];
    }
    result[i] = sum;
  }
  return result;
} */

Pattern WeightMatrix::operator*(const Pattern& pat)
{
  if (N_ != pat.size()) {
    throw std::invalid_argument(
        "WeightMatrix dimension must match Pattern size");
  }
  auto sign = [](float n) { return (n > 0) - (n < 0); };
  std::vector<int> result(N_, 0.f);

  for (size_t i{0}; i < N_; ++i) {
    float sum{0.f};
    for (size_t j{0}; j < N_; ++j) {
      sum += (*this)[i, j] * static_cast<float>(pat[j]);
      std::cout << "(*this)[i, j]: " << (*this)[i, j] << "   ";
      std::cout << "static_cast<float>(pat[j]) " << static_cast<float>(pat[j])
                << "   ";

      std::cout << "sum: " << sum << '\n';
    }
    result[i] = sign(sum);
    std::cout << "sign(sum): " << sign(sum) << "\n\n";

  }

  return result;
}
/* PRIMA VERSIONE
std::vector<float> WeightMatrix::operator*(const std::vector<float>& vec)
{
std::vector<float> result;
for (int i{0}; i != N_; ++i) {
int j{0};
result.push_back(
    std::accumulate(vec.begin(), vec.end(), 0.f, [&](float acc, float val) {
      float res{val * (*this)[i, j]};
      ++j;
      return acc + res;
    }));
}
return result;
}*/

} // namespace hpn