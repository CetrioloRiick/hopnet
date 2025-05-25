#include "recall.hpp"
#include "../common/weight_matrix.hpp"
#include <cstddef>
#include <vector>

namespace hpn {
std::vector<float> WeightMatrix::operator*(const std::vector<float>& vec)
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