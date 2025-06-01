#include "train/pattern.hpp"
#include <algorithm>
#include <array>
#include <stdexcept>
#include <string>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "common/input.hpp"
#include "common/weight_matrix.hpp"

using namespace hpn;
/* TEST_CASE("Testing loadVector")
{
  std::vector<float> expectedNumbers{1.9f, 2.4f, 5.4f, 6.0f, 0.9f};
  std::vector<float> effectivedNumbers{hpn::loadVector<float>("vectorTest.txt")};
  CHECK(expectedNumbers == effectivedNumbers);
} */

TEST_CASE("Testing WeightMatrix")
{
  std::array<std::array<float, 4>, 4> expectedMatrix{
      std::array<float, 4>{0, -0.5, -0.5, 0.5}, std::array<float, 4>{-0.5, 0, 0.5, -0.5},
      std::array<float, 4>{-0.5, 0.5, 0, -0.5}, std::array<float, 4>{0.5, -0.5, -0.5, 0}};

  Pattern::setSize(4);
  Pattern pat1{std::vector<int>{-1, 1, 1, -1}};
  Pattern pat2{std::vector<int>{1, -1, -1, 1}};
  WeightMatrix effectivedMatrix{4};
  CHECK(effectivedMatrix.effectiveSize() == 6);

  effectivedMatrix.hebbRule(pat1);
  effectivedMatrix.hebbRule(pat2);
  for (size_t i{0}; i != 4; ++i) {
    for (size_t j{0}; j != 4; ++j) {
      CHECK(effectivedMatrix[i, j] == expectedMatrix[i][j]);
    }
  }
  SUBCASE("bho")
  {
    CHECK_THROWS_AS(WeightMatrix(3, {1, 1}), std::invalid_argument);
    CHECK_THROWS_AS(effectivedMatrix.operator[](0,4), std::invalid_argument);
  }
}