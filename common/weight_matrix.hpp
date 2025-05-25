#include <filesystem>
#include <vector>

namespace hpn {
class Pattern;

class WeightMatrix
{
 public:
  // Common functions
  WeightMatrix(int N);
  std::vector<float> getWeights() const;

  // Train functions
  void hebbRule(const Pattern& image);
  void hebbRule(const std::vector<Pattern>& images);
  void save(const std::filesystem::path& file) const;

  // Recall functions

 private:
  int N_;
  int effectiveEl_;
  std::vector<float> weights_;
};
} // namespace hpn