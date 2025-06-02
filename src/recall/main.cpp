#include "common/weight_matrix.hpp"
#include "recall/input.hpp"
#include "recall/neural_network.hpp"
#include "recall/utils.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
  try {
    hpn::RecallOptions options{hpn::getRecallOpt(argc, argv)};

    hpn::NeuralNetwork::setSize(options.neuronCount());
    hpn::WeightMatrix weights{options.neuronCount(),
                              hpn::loadVector<double>(options.weightsFile)};

    hpn::NeuralNetwork corruptedPattern{hpn::loadVector<int>(options.inputFile)};
    corruptedPattern.randomize(options.noiseProbability);

    if (options.monitorFlag) {
      hpn::displayBinImage(corruptedPattern.getNeuronsValue(), options.width,
                           options.height);
    }

    corruptedPattern.minimizeState(weights, options.monitorFlag);
    corruptedPattern.save(options.outputFile);

    if (options.monitorFlag) {
      hpn::displayBinImage(corruptedPattern.getNeuronsValue(), options.width,
                           options.height);
    }
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
}