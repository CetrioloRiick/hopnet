#include "train.hpp"
#include "../common/input.hpp"
#include <iostream>
#include <vector>

int hpn::Pattern::pixelCount_ = 10;
int main(int argc, char* argv[])
{
  try {
    hpn::TrainOptions opt{hpn::getTrainOpt(argc, argv)};
    std::vector<hpn::Pattern> pippe{hpn::loadPatterns(opt.inputFile)};
    for (const hpn::Pattern& i : pippe) {
      for (size_t ind{0}; ind != 10; ++ind) {
        std::cout << i[ind];
      }
      std::cout << "\n\n";
    }
    for (size_t i{0}; i < 10; ++i) {
      std::cout << pippe[0][i];
    }

  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
  return 0;
}