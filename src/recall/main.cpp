#include "common/input.hpp"
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

    hpn::NeuralNetwork image{hpn::loadVector<int>(options.inputFile)};
    image.randomize(options.noiseProbability);

    hpn::displayImage(image.getNeuronsValue(), options.width, options.height);
    std::cout << image.getEnergy(weights) << '\n';
    image.minimizeState(weights, options.monitorFlag);


    hpn::displayImage(image.getNeuronsValue(), options.width, options.height);

    std::cout << "\n\n";
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
}