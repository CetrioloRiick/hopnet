#include "recall.hpp"
#include "../common/input.hpp"
#include "../common/pattern.hpp"
#include "../common/weight_matrix.hpp"

#include <cstddef>
#include <iostream>

int main(int argc, char* argv[])
{
  try {
    hpn::RecallOptions options{hpn::getRecallOpt(argc, argv)};
    // hpn::WeightMatrix weights{options.patternSize};
    hpn::Pattern::setSize(options.patternSize);
    // std::cout << "1\n";
    hpn::WeightMatrix weights{options.patternSize,
                              hpn::loadVector<float>(options.weightsFile)};
    // std::cout << "2\n";

    hpn::Pattern image{hpn::loadVector<int>(options.inputFile)};
    // std::cout << "3\n";
    hpn::Pattern image1{image};
    //std::cout << "4\n";
    int pluto{0};
    do {
            ++pluto;

      image1 = image;
//      std::cout << "5\n";
      image = weights * image;
    } while (pluto == 11);
 //   std::cout << "6\n";
    for (size_t i{0}; i < 4; ++i) {
      std::cout << "pixelValue: " << image.getPixelsValue()[i] << " | ";
    }
    std::cout << "\n\n";
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
  return 0;
}