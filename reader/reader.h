#pragma once
#include <string>
#include <vector>

class Reader{
public:
    Reader(const std::string& input_file);

    std::vector<std::pair<std::string, double>> getMeanGoalsPerGame() const;

private:
    std::vector<std::pair<std::string, double>> m_mean_goals_per_game;
};