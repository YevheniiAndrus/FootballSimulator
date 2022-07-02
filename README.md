# FootballSimulator

Simulates footbal tournament based on parameters such mean goals per game and goal distribution for each team.
Simulator produces tournament table after played season as CSV file. 
Each line contains team name, total points after season, number of won/drawn/loosed games and total number of scored/conceded goals

1. Clone repository.
2. Make sure you are on master branch: git checkout master
3. Update submodules to be able run googletests: git submodule update --init --recursive
4. mkdir build && cd build
5. cmake ..
6. make
7. Run simulator providing path to file MeanGoalPerGame.csv, i.e. ./ArringoTest path_to_MeanGoalPerGame.csv
8. Inspect results in current directory. Output printed into file results.csv
