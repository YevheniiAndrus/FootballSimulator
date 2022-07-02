// Standard headers.
#include <iostream>
#include <map>
#include <random>
#include <fstream>

#include "reader/reader.h"
#include "simulator/simulator.h"

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

void dump_results(const std::unordered_map<std::string, Record>& result){
  std::vector<std::pair<std::string, Record>> sorted(result.begin(), result.end());
    std::sort(sorted.begin(), sorted.end(), [](const std::pair<std::string, Record>& p1,
                                                         const std::pair<std::string, Record>& p2){
        if(p1.second.points == p2.second.points){
            return p1.second.total_goals_scored > p2.second.total_goals_scored;
        }

        return p1.second.points > p2.second.points;
    });

    std::ofstream output("results.csv");
    output << "TeamName,Points,GamesWonCount,GamesDrawnCount,GamesLostCount,TotalGoalsScored,TotalGoalsConceded" << std::endl;

    for(const auto& it : sorted){
      output << it.first << ","
             << it.second.points << ","
             << it.second.games_won_count << ","
             << it.second.games_drawn_count << ","
             << it.second.games_lost_count << ","
             << it.second.total_goals_scored << ","
             << it.second.total_goals_conceded << std::endl;
    }
}

int main(int argc, char* argv[])
{
  Reader reader(argv[1]);
  std::vector<std::pair<std::string, double>> ret = reader.getMeanGoalsPerGame();
  Simulator simulator;
  simulator.run(ret, GetGoalDistribution);
  dump_results(simulator.getResults());
  

  return EXIT_SUCCESS;
}
