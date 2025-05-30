#include "recall/input.hpp"
#include "common/input.hpp"
#include "common/pattern.hpp"
#include "common/weight_matrix.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
  try {
    hpn::RecallOptions options{hpn::getRecallOpt(argc, argv)};
    hpn::Pattern::setSize(options.patternSize);
    hpn::WeightMatrix weights{options.patternSize,
                              hpn::loadVector<float>(options.weightsFile)};
    hpn::Pattern image{hpn::loadVector<int>(options.inputFile)};
    
    
    hpn::Pattern image1{image};
    int pluto{0};
    do {
            ++pluto;

      image.stocazzo(weights);
//      std::cout << "5\n";
    } while (pluto == 2);
 //   std::cout << "6\n";

 
    for (size_t i{0}; i < 4; ++i) {
      std::cout << "pixelValue: " << image.getPixelsValue()[i] << " | ";
    }
    std::cout << "\n\n";
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
  
}