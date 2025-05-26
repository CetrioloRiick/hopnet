#include <algorithm>
#include <vector>
#include "../common/weight_matrix.hpp"

namespace hpn {
std::vector<int> sign(const std::vector<float>& vec)
{
  std::vector<int> result(vec.size());
  std::transform(vec.begin(), vec.end(), result.begin(),
                 [](float x) { return (0 < x) - (x < 0); });
                 
  return result;
}
} // namespace hpn