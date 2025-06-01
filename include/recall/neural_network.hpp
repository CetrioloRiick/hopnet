#ifndef RECALL_NEURAL_NETWORK_HPP
#define RECALL_NEURAL_NETWORK_HPP
#include <cstddef>
#include <filesystem>
#include <string>
#include <vector>

namespace hpn {
class WeightMatrix;

class NeuralNetwork
{
 public:
  NeuralNetwork(const std::string& buffer);
  NeuralNetwork(const std::vector<int>& pV);
  std::vector<int> getNeuronsValue() const;
  void randomize(float prob);
  float getEnergy(const WeightMatrix& wm) const;
  // int operator[](size_t index) const;
  // Pattern(const Pattern& other) = default;
  // bool operator!=(const hpn::Pattern&) const = delete;
  // bool operator!=(const hpn::Pattern&) const;

  static void setSize(size_t n);
  size_t size() const;

  void minimizeState(const WeightMatrix& mat, bool monitor);
  // int operator[](int index) const;

 private:
  static size_t size_;
  std::vector<int> pixelsValue_;
  std::vector<int> oldNeurons_;
  bool updateState(const WeightMatrix& mat);
  int& operator[](size_t index);

};

} // namespace hpn
#endif