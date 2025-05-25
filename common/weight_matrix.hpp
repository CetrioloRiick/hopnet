#include <cstddef>
#include <filesystem>
#include <vector>

namespace hpn {
class Pattern;

class WeightMatrix
{
 public:
  // Common functions
  WeightMatrix(size_t N);
  std::vector<float> getWeights() const;
  float operator[](size_t i, size_t j);

  // Train functions
  void hebbRule(const Pattern& image);
  void hebbRule(const std::vector<Pattern>& images);
  void save(const std::filesystem::path& file) const;

  // Recall functions
  std::vector<float> operator*(const std::vector<float>& vec);

 private:
  size_t N_;
  size_t effectiveEl_;
  std::vector<float> weights_;
};
} // namespace hpn