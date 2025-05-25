#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <cstddef>
#include <filesystem>
#include <vector>

namespace hpn {
class Pattern
{
 public:
  Pattern(const std::string& buffer);
  std::vector<int> getPixelsValue() const;
  int operator[](size_t index) const;
  int operator[](int index) const;

 private:
  static int pixelCount_;
  std::vector<int> pixelsValue_;
};
std::vector<Pattern> loadPatterns(const std::filesystem::path& path);

class WeightMatrix
{
 public:
  WeightMatrix(int N);
  void hebbRule(const Pattern& image);
  void hebbRule(const std::vector<Pattern>& images);
  std::vector<float> getWeights() const;
  void save(const std::filesystem::path& file) const;

 private:
  int N_;
  int effectiveEl_;
  std::vector<float> weights_;
};
} // namespace hpn

#endif