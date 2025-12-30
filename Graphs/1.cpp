#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct edge {
    int to;
    int price;
    int time;
};

struct state {
    int city;
    int total_price;
    int total_time;
    int total_flights;
};

//compare priority
bool is_better(const state& a, const state& b, const vector<int>& filters) {
    for (int i = 0; i < filters.size(); i++) {
        int f = filters[i];
        if (f == 1 && a.total_price != b.total_price)
            return a.total_price < b.total_price;
        if (f == 2 && a.total_time != b.total_time)
            return a.total_time < b.total_time;
        if (f == 3 && a.total_flights != b.total_flights)
            return a.total_flights < b.total_flights;
    }
    return false;
}

int get_city(vector<string>& cities, const string& name) {
    for (int i = 0; i < cities.size(); i++) {
        if (cities[i] == name) return i;
    }
    cities.push_back(name);
    return cities.size() - 1;
}

int main() {
    int m, n_filters;
    cin >> m >> n_filters;

    vector<string> cities;
    vector<vector<edge>> adj;

    //parsing
    for (int i = 0; i < m; i++) {
        string from, to;
        int price, time;
        cin >> from >> to >> price >> time;

        int u = get_city(cities, from);
        int v = get_city(cities, to);

        int max_index = (u > v) ? u : v;
        if (adj.size() <= max_index) {
            adj.resize(max_index + 1);
        }

        adj[u].push_back({v,price,time});
    }

    vector<int> filters(n_filters);
    for (int i = 0; i < n_filters; i++) {
        cin >> filters[i];
    }

    int start = get_city(cities, "Taipei");
    int target = get_city(cities, "Stockholm");

    //string start_name, target_name;
    //cin >> start_name >> target_name;

    // start = get_city(cities, start_name);
    //int target = get_city(cities, target_name);

    int n = cities.size();

    int inf = 1000000000;
    vector<state> best(n, {0, inf, inf, inf});
    vector<int> parent(n, -1);
    queue<state> q;

    best[start] = {start, 0, 0, 0};
    q.push(best[start]);

    while (!q.empty()) {
        state current = q.front();
        q.pop();

        if (current.city == target) continue;
        if (is_better(best[current.city], current, filters)) continue;

        for (int i = 0; i < adj[current.city].size(); i++) {
            edge e = adj[current.city][i];
            state next;
            next.city = e.to;
            next.total_price = current.total_price + e.price;
            next.total_time = current.total_time + e.time;
            next.total_flights = current.total_flights + 1;

            if (is_better(next, best[e.to], filters)) {
                best[e.to] = next;
                parent[e.to] = current.city;
                q.push(next);
            }
        }
    }

    cout << best[target].total_price << endl;

    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }

    for (int i = path.size() - 1; i >= 0; i--) {
        cout << cities[path[i]];
        if (i > 0) cout << "->";
    }
    cout << endl;

    return 0;
}
