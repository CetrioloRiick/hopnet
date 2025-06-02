#ifndef COMMON_PATTERN_HPP
#define COMMON_PATTERN_HPP
#include <filesystem>
#include <string>
#include <vector>

namespace hpn {
class WeightMatrix;

class Pattern
{
 public:
  Pattern(const std::string& buffer);
  std::vector<int> getPixelsValue() const;

  int operator[](size_t index) const;

  static void setSize(size_t n);
  size_t size() const;

 private:
  static size_t size_;
  std::vector<int> pixelsValue_;
};

std::vector<Pattern> loadPatterns(const std::filesystem::path& path);

} // namespace hpn
#endif