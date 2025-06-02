#ifndef RECALL_NEURAL_NETWORK_HPP
#define RECALL_NEURAL_NETWORK_HPP
#include <filesystem>
#include <vector>

namespace hpn {
class WeightMatrix;

class NeuralNetwork
{
 public:
  NeuralNetwork(const std::vector<int>& n);
  std::vector<int> getNeuronsValue() const;
  void randomize(double prob);

  static void setSize(size_t n);
  size_t size() const;

  void minimizeState(const WeightMatrix& mat, bool monitor);
  double getEnergy(const WeightMatrix& wm) const;
  void save(const std::filesystem::path& path) const;

 private:
  static size_t size_;
  std::vector<int> neurons_;
  std::vector<int> oldNeurons_;
  bool updateState(const WeightMatrix& mat);
  int& operator[](size_t index);
};
} // namespace hpn
#endif