#include "train/pattern.hpp"
#include "common/weight_matrix.hpp"
#include "train/input.hpp"
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
  try {
    hpn::TrainOptions options{hpn::getTrainOpt(argc, argv)};
    hpn::Pattern::setSize(options.patternSize);
    hpn::WeightMatrix weights{options.patternSize};

    std::vector<hpn::Pattern> trainingSet{hpn::loadPatterns(options.inputFile)};
    
    weights.hebbRule(trainingSet);
    weights.save(options.outputFile);
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
}
