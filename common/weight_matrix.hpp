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
  float operator[](size_t i, size_t j) const;

  // Train functions
  void hebbRule(const Pattern& image);
  void hebbRule(const std::vector<Pattern>& images);
  void save(const std::filesystem::path& file) const;

  // Recall functions
  //std::vector<float> operator*(const std::vector<float>& vec);
  Pattern operator*(const Pattern& pat);
  WeightMatrix(size_t N, const std::vector<float>& weights);
  size_t getN() const;
  size_t effectiveSize() const;

 private:
  size_t N_;
  //size_t effectiveSize_;
  //size_t effectiveSize();
  std::vector<float> weights_;
};
} // namespace hpn