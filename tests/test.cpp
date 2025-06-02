#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "common/weight_matrix.hpp"
#include "recall/neural_network.hpp"
#include "train/pattern.hpp"

#include <array>
#include <stdexcept>
#include <string>
#include <vector>

using namespace hpn;

TEST_CASE("Pattern class tests")
{
  Pattern::setSize(4);

  CHECK_NOTHROW(Pattern("1          1         -1  \n-1"));

  CHECK_THROWS_AS(Pattern::setSize(6), std::runtime_error);
  CHECK_THROWS_AS(Pattern("1 1 1"), std::invalid_argument);

  CHECK_THROWS_AS(Pattern("1 2 3 4"), std::invalid_argument);
  CHECK_THROWS_AS(Pattern("avcsg"), std::invalid_argument);

  Pattern pattern{"-1 1 1 -1"};
  std::vector<int> expectedValues{-1, 1, 1, -1};
  CHECK(pattern.getPixelsValue() == expectedValues);
}

TEST_CASE("NeuralNetwork class tests")
{
  NeuralNetwork::setSize(4);

  CHECK_NOTHROW(NeuralNetwork({1, -1, 1, -1}));

  CHECK_THROWS_AS(NeuralNetwork::setSize(6), std::runtime_error);
  CHECK_THROWS_AS(NeuralNetwork({1, 1, 1, 1, 1}), std::invalid_argument);

  CHECK_THROWS_AS(NeuralNetwork({1, 2, 3, 4}), std::invalid_argument);
}

TEST_CASE("WeightMatrix class tests")
{
  constexpr size_t matrixSize{4};
  WeightMatrix weights(matrixSize);

  SUBCASE("WeightMatrix: correct effective size")
  {
    CHECK(weights.effectiveSize() == 6);
  }

  SUBCASE("WeightMatrix: Hebb rule computation")
  {
    Pattern pattern1{"-1 1 1 -1"};
    Pattern pattern2{"1 -1 -1 1"};

    weights.hebbRule(pattern1);
    weights.hebbRule(pattern2);

    std::array<std::array<double, matrixSize>, matrixSize> expectedWeights{
        std::array<double, 4>{0, -0.5, -0.5, 0.5},
        std::array<double, 4>{-0.5, 0, 0.5, -0.5},
        std::array<double, 4>{-0.5, 0.5, 0, -0.5},
        std::array<double, 4>{0.5, -0.5, -0.5, 0}};

    for (size_t i = 0; i != matrixSize; ++i) {
      for (size_t j = 0; j != matrixSize; ++j) {
        CHECK(weights[i, j] == doctest::Approx(expectedWeights[i][j]));
      }
    }
  }

  SUBCASE("WeightMatrix: invalid construction and access")
  {
    CHECK_THROWS_AS(WeightMatrix(3, {1, 1}), std::invalid_argument);
    CHECK_THROWS_AS(weights.operator[](0, 4), std::invalid_argument);
  }
}

TEST_CASE("NeuralNetwork energy minimization and state update")
{
  constexpr size_t matrixSize = 4;
  Pattern pattern1{"-1 1 1 -1"};
  Pattern pattern2{"1 -1 -1 1"};
  WeightMatrix weights(matrixSize);
  weights.hebbRule(pattern1);
  weights.hebbRule(pattern2);

  NeuralNetwork network({1, -1, 1, -1});

  SUBCASE("Energy computation")
  {
    double expectedEnergy = 1.0f;
    CHECK(doctest::Approx(network.getEnergy(weights)) == expectedEnergy);
  }

  SUBCASE("Energy minimization and convergence")
  {
    network.minimizeState(weights, false);
    std::vector<int> expectedState{-1, 1, 1, -1};
    CHECK(network.getNeuronsValue() == expectedState);
  }
}
