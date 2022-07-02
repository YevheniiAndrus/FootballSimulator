#pragma once

#include <vector>
#include <functional>
#include <string>
#include <map>
#include <unordered_map>

struct Record
{
    int points = 0;
    int games_won_count = 0;
    int games_drawn_count = 0;
    int games_lost_count = 0;
    int total_goals_scored = 0;
    int total_goals_conceded = 0;
};

class Simulator
{
public:
    void run(const std::vector<std::pair<std::string, double>> &mean_goals_per_game,
             std::function<std::map<uint32_t, double>(double)> distr);

    std::unordered_map<std::string, Record> getResults() const {return m_table;}

private:
    void playGame(const std::string &host_name, const std::string &guest_name, int host_goals, int guest_goals);

    static double generate_goal_distribution(double range_start, double range_end);
    static int calculate_scored_goals(double goal_distibution, std::map<uint32_t, double> &&probabilities);

private:
    std::unordered_map<std::string, Record> m_table;
};