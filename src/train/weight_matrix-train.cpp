#include "common/weight_matrix.hpp"
#include "train/pattern.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <fstream>

namespace hpn {
void WeightMatrix::hebbRule(const Pattern& sample)
{
  size_t indexI{0};
  size_t indexJ{1};
  // Indici della matrice
  std::for_each_n(weights_.begin(), effectiveSize(), [&](double& val) {
    assert(indexI < indexJ);
    val += static_cast<double>(sample[indexI] * sample[indexJ]) / static_cast<double>(N_);
    if (indexJ != N_ - 1) {
      indexJ++;
    } else {
      indexI++;
      indexJ = indexI + 1;
    }
  });
}

void WeightMatrix::hebbRule(const std::vector<Pattern>& samples)
{
  std::for_each(samples.begin(), samples.end(),
                [&](const Pattern& pat) { hebbRule(pat); });
}

void WeightMatrix::save(const std::filesystem::path& path) const
{
  std::ofstream fout(path);
  std::for_each(weights_.begin(), weights_.end(),
                [&](const double& w) { fout << w << ' '; });
}

} // namespace hpn