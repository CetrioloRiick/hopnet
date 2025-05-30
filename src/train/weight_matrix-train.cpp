#include "common/weight_matrix.hpp"
#include "common/pattern.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <fstream>

namespace hpn {
void WeightMatrix::hebbRule(const Pattern& image)
{
  size_t indexI{0};
  size_t indexJ{1};
  // Indici della matrice
  std::for_each_n(weights_.begin(), effectiveSize(), [&](float& val) {
    assert(indexI < indexJ);
    val += static_cast<float>(image[indexI] * image[indexJ])
         / static_cast<float>(N_);
    if (indexJ != N_ - 1) {
      indexJ++;
    } else {
      indexI++;
      indexJ = indexI + 1;
    }
  });
  //Valuta il costum iterator
}

/* VERSIONE CON ITERATORI
void WeightMatrix::hebbRule(const Pattern& image)
{
int num{((N_ * N_) - N_) / 2};
auto pluto    = image.getPixelsValue().begin();
auto paperino = image.getPixelsValue().begin();
int index{0};
int index2{0};
std::for_each_n(weights_.begin(), num, [&](float& pippo) {
if (index != index2) {
  pippo +=
      static_cast<float>((*pluto) * (*paperino)) / static_cast<float>(N_);
}
if (index2 != N_ - 1) {
  paperino++;
} else {
  pluto++;
  paperino=image.getPixelsValue().begin();
  paperino+=pluto;
}

});
}*/

void WeightMatrix::hebbRule(const std::vector<Pattern>& images)
{
  std::for_each(images.begin(), images.end(),
                [&](const Pattern& pippo) { hebbRule(pippo); });
}

void WeightMatrix::save(const std::filesystem::path& path) const
{
  std::ofstream fout(path);
  std::for_each(weights_.begin(), weights_.end(),
                [&](const float& w) { fout << w << ' '; });
}

} // namespace hpn