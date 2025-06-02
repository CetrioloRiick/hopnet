#ifndef COMMON_WEIGHT_MATRIX_HPP
#define COMMON_WEIGHT_MATRIX_HPP
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
  double operator[](size_t i, size_t j) const;

  // Train functions
  void hebbRule(const Pattern& image);
  void hebbRule(const std::vector<Pattern>& images);
  void save(const std::filesystem::path& file) const;

  // Recall functions
  //std::vector<double> operator*(const std::vector<double>& vec);
  WeightMatrix(size_t N, const std::vector<double>& weights);
  size_t getN() const;
  size_t effectiveSize() const;

 private:
  size_t N_;
  size_t effectiveSize_;
  //size_t effectiveSize();
  std::vector<double> weights_;
};
} // namespace hpn
#endif