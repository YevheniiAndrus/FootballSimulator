#include <gtest/gtest.h>
#include "../simulator.h"

#include <cmath>

/**
 * Computes the goal cumulative probability distribution.
 * Note:
 * - Allowed goals per match vary in the range [0, 5] (inclusive)
 * - std::map::key ----> Goal count
 * - std::map::value --> Cumulative probability
 *
 * @param meanGoalPerMatch   Arithmetic mean goal per match.
 * @return                   Probability distribution map.
 */
std::map<uint32_t, double> GetGoalDistribution(const double meanGoalPerMatch)
{
  constexpr auto lbdFactorial{ [](const uint32_t factorial) {
    auto result{ 1u };
    for (uint32_t idx = 1u; idx <= factorial; ++idx)
    {
      result *= idx;
    }
    return result;
  } };

  constexpr auto maxGoals{ 5u };

  auto prevProbability{ 0.0 };
  std::map<uint32_t, double> goalDist;
  for (uint32_t i = 0u; i < maxGoals; ++i)
  {
    const auto probPoisson{ (std::pow(meanGoalPerMatch, i) * std::exp(-1 * meanGoalPerMatch))
                / lbdFactorial(i) };

    goalDist.emplace(std::make_pair(i, (probPoisson + prevProbability)));
    prevProbability += probPoisson;
  }

  goalDist.emplace(std::make_pair(maxGoals, 1.0));

  return goalDist;
}

TEST(SimulatorTest, GeneralTest){
    Simulator simulator;
    std::vector<std::pair<std::string, double>> test_data{std::make_pair("Arsenal", 1.92105263157895),
                                                          std::make_pair("Cardiff", 0.294736842105263),
                                                          std::make_pair("ManCity", 2.5),
                                                          std::make_pair("ManUtd", 1.71052631578947),
                                                          std::make_pair("Liverpool", 0.194732841105263)};

    simulator.run(test_data, GetGoalDistribution);
    std::unordered_map<std::string, Record> res = simulator.getResults();

    EXPECT_TRUE(res["ManCity"].points > res["Cardiff"].points);
    EXPECT_TRUE(res["ManUtd"].points > res["Liverpool"].points);
    EXPECT_TRUE(res["Cardiff"].games_lost_count > res["Cardiff"].games_won_count);
    EXPECT_TRUE(res["Liverpool"].total_goals_scored > 0);
    EXPECT_TRUE(res["Liverpool"].total_goals_conceded > 5);
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}