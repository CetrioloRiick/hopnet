#include "train.hpp"
#include "../common/input.hpp"
#include <iostream>
#include <vector>

int hpn::Pattern::pixelCount_ = 100;
int main(int argc, char* argv[])
{
  try {
    hpn::TrainOptions opt{hpn::getTrainOpt(argc, argv)};
    std::vector<hpn::Pattern> pippe{hpn::loadPatterns(opt.inputFile)};
    for (const hpn::Pattern& i : pippe) {
      for (size_t ind{0}; ind != 100; ++ind) {
        std::cout << i[ind];
      }
      std::cout << "\n\n";
    }
    hpn::WeightMatrix artanis{10};
    artanis.hebbRule(pippe);
    auto pluto{artanis.getWeights()};
    for (const auto& i : pluto) {
      std::cout << i << " ";
    }
    artanis.save(opt.outputFile);
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
  return 0;
}