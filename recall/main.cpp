#include "recall.hpp"
#include "../common/input.hpp"
#include "../common/weight_matrix.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
  try {
    hpn::RecallOptions options{hpn::getRecallOpt(argc, argv)};
   // hpn::WeightMatrix weights{options.patternSize};

    hpn::WeightMatrix weights{hpn::loadVector(options.weightsFile)};
    hpn::Pattern image{hpn::loadPatterns(options.inputFile)};
    
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
  return 0;
}