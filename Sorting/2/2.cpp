#include "function.h"

#include <iomanip>

using namespace std;

unordered_map<string, int> nameToId;
unordered_map<string, Team> divisionLeaders;

double winRate(const Team& t) {
    auto total = t.win + t.loss;
    return (double)t.win / total;
}

double divisionWinRate(const Team& t) {
    auto total = t.divisionWin + t.divisionLoss;
    return (double)t.divisionWin / total;
}

bool compare(const Team& a, const Team& b, bool retro, const unordered_map<string, Team>& leaders) {
    const double EPS = 1e-8;

    if (retro) {
        bool isALeader = (leaders.count(a.division) && leaders.at(a.division).name == a.name);
        bool isBLeader = (leaders.count(b.division) && leaders.at(b.division).name == b.name);

        if (isALeader && !isBLeader) return true;
        if (!isALeader && isBLeader) return false;
    }

    auto wrA = winRate(a), wrB = winRate(b);
    if (abs(wrA - wrB) > EPS) return wrA > wrB;
    if (a.pointDiff != b.pointDiff) return a.pointDiff > b.pointDiff;
    auto dwrA = divisionWinRate(a), dwrB = divisionWinRate(b);
    if (abs(dwrA - dwrB) > EPS) return dwrA > dwrB;
    return a.name < b.name;
}

void sorting(vector<Team>& arr, int l, int r, bool retro, const unordered_map<string, Team>& leaders) {
    sort(arr.begin(), arr.end(), [&](const Team& a, const Team& b) {
        return compare(a, b, retro, leaders);
        });
}

int main() {
    int N, G;
    cin >> N >> G;
    vector<Team> teams(N);
    for (auto i = 0; i < N; i++) {
        string name, division;
        cin >> name >> division;
        teams[i] = { name, division, i };
        nameToId[name] = i;
    }
    for (auto i = 0; i < G; i++) {
        string a, b;
        int scoreA, scoreB;
        cin >> a >> b >> scoreA >> scoreB;
        int idA = nameToId[a];
        int idB = nameToId[b];
        Team& teamA = teams[idA], & teamB = teams[idB];
        if (scoreA > scoreB) {
            teamA.win++; teamB.loss++;
            if (teamA.division == teamB.division) teamA.divisionWin++, teamB.divisionLoss++;
        }
        else {
            teamB.win++; teamA.loss++;
            if (teamA.division == teamB.division) teamB.divisionWin++, teamA.divisionLoss++;
        }
        teamA.pointDiff += scoreA - scoreB;
        teamB.pointDiff += scoreB - scoreA;
    }
    string retroStr;
    cin >> retroStr;
    bool retro = (retroStr == "true");
    if (retro) {
        for (const auto& t : teams) {
            auto& currentLeader = divisionLeaders[t.division];
            if (compare(t, currentLeader, false, divisionLeaders)) {
                divisionLeaders[t.division] = t;
            }
        }
    }
    sorting(teams, 0, N - 1, retro, divisionLeaders);
    for (int i = 0; i < teams.size(); i++) {
        cout << i + 1 << ". " << teams[i].name << " " << teams[i].win << "-" << teams[i].loss << endl;
    }
}