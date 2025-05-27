#include <filesystem>
#include <string>
#include <vector>

namespace hpn {
class WeightMatrix;

class Pattern
{
 public:
  Pattern(const std::string& buffer);
  Pattern(const std::vector<int>& pV);
  std::vector<int> getPixelsValue() const;

  int operator[](size_t index) const;
  // Pattern(const Pattern& other) = default;
  //bool operator!=(const hpn::Pattern&) const = delete;
  bool operator!=(const hpn::Pattern&) const;

  static void setSize(size_t n);
  size_t size() const;

  void stocazzo(const WeightMatrix& mat);
  // int operator[](int index) const;

 private:
  static size_t size_;
  std::vector<int> pixelsValue_;
};
std::vector<Pattern> loadPatterns(const std::filesystem::path& path);
} // namespace hpn