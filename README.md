# FootballSimulator

Simulates footbal tournament based on parameters such mean goals per game and goal distribution for each team.
Simulator produces tournament table after played season as CSV file. 
Each line contains team name, total points after season, number of won/drawn/loosed games and total number of scored/conceded goals

1. Clone repository.
2. Update submodules to be able run googletests: git submodule init --update --recursive
3. mkdir build && cd build
4. cmake ..
5. make
6. Run simulator providing path to file MeanGoalPerGame.csv, i.e. ./ArringoTest path_to_MeanGoalPerGame.csv
7. Inspect results in current directory. Output printed into file results.csv
