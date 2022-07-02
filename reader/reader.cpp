#include "reader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Reader::Reader(const std::string& input_file){
    std::ifstream goal_file(input_file);
    if(!goal_file.is_open()){
        std::cout << "Not found" << std::endl;
    }

    std::string line;

    // skip first line
    std::getline(goal_file, line);

    // read file line by line
    while(std::getline(goal_file, line)){
        std::istringstream tokens(line);

        // read token separated by comma
        // since we already know that each record has always two tokens - command name and mean goals per game
        // we can directly store them in dictionary

        // read team name
        std::string team_name;
        std::getline(tokens, team_name, ',');

        // read mean goals per game
        std::string mean_goals_per_game;
        std::getline(tokens, mean_goals_per_game);

        m_mean_goals_per_game.push_back(std::make_pair(team_name, std::atof(mean_goals_per_game.c_str())));
    }
}

std::vector<std::pair<std::string, double>>
Reader::getMeanGoalsPerGame() const{
    return m_mean_goals_per_game;
}