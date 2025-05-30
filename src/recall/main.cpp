#include "common/input.hpp"
#include "common/weight_matrix.hpp"
#include "recall/input.hpp"
#include "recall/neural_network.hpp"
#include "recall/utils.hpp"

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
  try {
    hpn::RecallOptions options{hpn::getRecallOpt(argc, argv)};
    hpn::NeuralNetwork::setSize(options.patternSize);
    hpn::WeightMatrix weights{options.patternSize,
                              hpn::loadVector<float>(options.weightsFile)};

    hpn::NeuralNetwork image{hpn::loadVector<int>(options.inputFile)};

    hpn::displayImage(image.getNeuronsValue(), 50, 50);
    hpn::NeuralNetwork image1{image};

    image.minimizeState(weights, options.monitorFlag);

    //      std::cout << "5\n";

    //   std::cout << "6\n";

    hpn::displayImage(image.getNeuronsValue(), 50, 50);

    std::cout << "\n\n";
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
}