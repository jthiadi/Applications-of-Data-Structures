#ifndef PARTIAL_H
#define PARTIAL_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <sstream>
#include <string>

//Team information
struct Team {
    std::string name;                           //Team name
    std::string division;                       //Team division
    int id;
    int win = 0, loss = 0;                      //current number of wins/losses
    int divisionWin = 0, divisionLoss = 0;      //current number of division wins/losses
    int pointDiff = 0;                          //current accumulation of points differentiation
};

// Declare global variables, do NOT define here
// Mapping team name to id
extern std::unordered_map<std::string, int> nameToId;

// lists of divisionLeaders
extern std::unordered_map<std::string, Team> divisionLeaders;

// Calculate win rate
double winRate(const Team& t);

// Comparison with tie-breaking condition
bool compare(const Team& a, const Team& b, bool retro, const std::unordered_map<std::string, Team>& divisionLeaders);

// Sorting method
void sorting(std::vector<Team>& arr, int l, int r, bool retro, const std::unordered_map<std::string, Team>& leaders);
#endif

