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
  int operator[](size_t index) const ;


 private:
  static int pixelCount_;
  std::vector<int> pixelsValue_;
};
std::vector<Pattern> loadPatterns(const std::filesystem::path& path);

class WeightMatrix
{
 public:
  WeightMatrix();

 private:
  std::vector<float> weights_;
};
} // namespace hpn

#endif