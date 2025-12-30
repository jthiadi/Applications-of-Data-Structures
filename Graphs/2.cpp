#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 10000000;

struct Edge {
    int to, time, line;
};

struct State {
    int cost, station, lineState;
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

int main() {
    cin.tie(nullptr);
    
    int m, f, P;
    if (!(cin >> m >> f >> P)) return 0;
    
    unordered_map<string, int> stationMap;
    vector<string> stationNames;
    unordered_map<string, int> lineMap;
    
    vector<vector<Edge>> adj;
    
    for (int i = 0; i < m; i++) {
        string u, v, line;
        int time;
        cin >> u >> v >> time >> line;
        
        if (!stationMap.count(u)) {
            stationMap[u] = stationNames.size();
            stationNames.push_back(u);
            adj.push_back({});
        }
        if (!stationMap.count(v)) {
            stationMap[v] = stationNames.size();
            stationNames.push_back(v);
            adj.push_back({});
        }
        if (!lineMap.count(line)) {
            lineMap[line] = lineMap.size();
        }
        
        auto uid = stationMap[u];
        auto vid = stationMap[v];
        auto lid = lineMap[line];
        
        adj[uid].push_back({vid, time, lid});
        adj[vid].push_back({uid, time, lid});
    }
    
    vector<int> starts(f);
    for (int i = 0; i < f; i++) {
        string s;
        cin >> s;
        if (!stationMap.count(s)) {
            stationMap[s] = stationNames.size();
            stationNames.push_back(s);
            adj.push_back({});
        }
        starts[i] = stationMap[s];
    }
    
    auto n = stationNames.size();
    auto numLines = lineMap.size();
    auto maxLineState = numLines + 1;
    
    vector<vector<vector<int>>> dist(f, vector<vector<int>>(n, vector<int>(maxLineState, INF)));
    vector<vector<vector<pair<int, int>>>> prev(f, vector<vector<pair<int, int>>>(n, vector<pair<int, int>>(maxLineState, {-1, -1})));
    
    for (int i = 0; i < f; i++) {
        priority_queue<State, vector<State>, greater<State>> pq;
        dist[i][starts[i]][0] = 0;
        pq.push({0, starts[i], 0});
        
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            
            if (cur.cost > dist[i][cur.station][cur.lineState]) continue;
            
            for (const auto& edge : adj[cur.station]) {
                auto newLineState = edge.line + 1;
                auto penalty = (cur.lineState != 0 && cur.lineState != newLineState) ? P : 0;
                auto newCost = cur.cost + edge.time + penalty;
                
                if (newCost < dist[i][edge.to][newLineState]) {
                    dist[i][edge.to][newLineState] = newCost;
                    prev[i][edge.to][newLineState] = {cur.station, cur.lineState};
                    pq.push({newCost, edge.to, newLineState});
                }
            }
        }
    }
    
    int bestStation = -1;
    auto bestSum = INF;
    vector<int> bestCosts;
    
    for (int station = 0; station < n; station++) {
        vector<int> costs(f);
        bool reachable = true;
        
        for (int i = 0; i < f; i++) {
            auto minCost = INF;
            for (int ls = 0; ls < maxLineState; ls++) {
                minCost = min(minCost, dist[i][station][ls]);
            }
            if (minCost == INF) {
                reachable = false;
                break;
            }
            costs[i] = minCost;
        }
        
        if (!reachable) continue;
        
        auto sum = 0;
        for (auto cost : costs) sum += cost;
        
        if (sum < bestSum || (sum == bestSum && costs < bestCosts)) {
            bestSum = sum;
            bestCosts = costs;
            bestStation = station;
        }
    }
    
    cout << bestSum << "\n" << stationNames[bestStation] << "\n";
    
    for (int i = 0; i < f; i++) {
        int bestLineState = 0;
        auto minCost = INF;
        for (int ls = 0; ls < maxLineState; ls++) {
            if (dist[i][bestStation][ls] < minCost) {
                minCost = dist[i][bestStation][ls];
                bestLineState = ls;
            }
        }
        
        vector<int> path;
        auto station = bestStation;
        auto lineState = bestLineState;
        
        while (station != -1) {
            path.push_back(station);
            auto p = prev[i][station][lineState];
            station = p.first;
            lineState = p.second;
        }
        
        reverse(path.begin(), path.end());
        
        for (int j = 0; j < path.size(); j++) {
            cout << stationNames[path[j]];
            if (j + 1 < path.size()) cout << "->";
        }
        if (i + 1 < f) cout << "\n";
    }
    
    return 0;
}