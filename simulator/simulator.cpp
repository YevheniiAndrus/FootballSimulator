#include "simulator.h"
#include <iostream>
#include <random>

double Simulator::generate_goal_distribution(double rangle_start, double range_end)
{
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_real_distribution<double> real_distr(0.0, 1.0);
    return real_distr(generator);
}

int Simulator::calculate_scored_goals(double goal_distribution, std::map<uint32_t, double> &&probabilities)
{
    double prev = 0.0;
    int goal_scored = 0;
    for (const auto &it : probabilities)
    {
        if (goal_distribution >= prev && goal_distribution < it.second)
        {
            goal_scored = it.first;
            break;
        }

        prev = it.second;
    }

    return goal_scored;
}

void Simulator::playGame(const std::string &host_name, const std::string &guest_name, int host_goals, int guest_goals)
{

    if (host_goals > guest_goals)
    {
        // update record for host team as a winner
        m_table[host_name].points += 3;
        m_table[host_name].games_won_count++;
        m_table[host_name].total_goals_scored += host_goals;
        m_table[host_name].total_goals_conceded += guest_goals;

        // update record for guest team as a looser
        m_table[guest_name].total_goals_conceded += host_goals;
        m_table[guest_name].total_goals_scored += guest_goals;
        m_table[guest_name].games_lost_count++;
    }
    else if (host_goals < guest_goals)
    {
        // update record for guest team as a winner
        m_table[guest_name].points += 3;
        m_table[guest_name].games_won_count++;
        m_table[guest_name].total_goals_scored += guest_goals;
        m_table[guest_name].total_goals_conceded += host_goals;

        // update record for host team as a looser
        m_table[host_name].total_goals_conceded += guest_goals;
        m_table[host_name].total_goals_scored += host_goals;
        m_table[host_name].games_lost_count++;
    }

    // update records for draw
    m_table[host_name].games_drawn_count++;
    m_table[host_name].points++;
    m_table[host_name].total_goals_scored += host_goals;
    m_table[host_name].total_goals_conceded += guest_goals;

    m_table[guest_name].points++;
    m_table[guest_name].games_drawn_count++;
    m_table[guest_name].total_goals_scored += guest_goals;
    m_table[guest_name].total_goals_conceded += host_goals;
}

void Simulator::run(const std::vector<std::pair<std::string, double>> &mean_goals_per_game,
                    std::function<std::map<uint32_t, double>(double)> distr)
{
    // iterator over dictionary and play game for every command
    // and store current result

    for (size_t i = 0; i < mean_goals_per_game.size(); ++i)
    {
        for (size_t j = 0; j < mean_goals_per_game.size(); ++j)
        {
            if (i == j)
                continue;

            // randomly generate goals distribution for host and guest teams
            int host_goals_scored = calculate_scored_goals(generate_goal_distribution(0.0, 1.0), distr(mean_goals_per_game[i].second));
            int guest_goals_scored = calculate_scored_goals(generate_goal_distribution(0.0, 1.0), distr(mean_goals_per_game[j].second));

            // play game for every pair and update tournament table after every game
            playGame(mean_goals_per_game[i].first, mean_goals_per_game[j].first,
                     host_goals_scored, guest_goals_scored);
        }
    }
}