#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;
#include <cmath>
const double EPSILON = 1e-9;
bool is_nearly_equal(double a, double b) {
    return fabs(a - b) < EPSILON;
}

const int MAX_NAME_LEN = 21;
const int INITIAL_CAPACITY = 100001;

// swap fx bwt pointers
template<typename T>
void swap(T*& first, T*& second) {
    T* temp = first;
    first = second;
    second = temp;
}

// bwt store individual player stats
class Player {
public:
    char name[MAX_NAME_LEN];
    int team_id;
    int games_played;
    double total_points;
    double total_rebounds;
    double total_assists;
    double total_fouls;

    // bwt player baru
    Player(const char* player_name, int team) {
        strncpy(name, player_name, MAX_NAME_LEN - 1);
        name[MAX_NAME_LEN - 1] = '\0';
        team_id = team;
        games_played = 0;
        total_points = total_rebounds = total_assists = total_fouls = 0;
    }

    // itung avg stats
    double get_avg_points() {
        return total_points / games_played;
    }

    double get_avg_rebounds() {
        return total_rebounds / games_played;
    }

    double get_avg_assists() {
        return total_assists / games_played;
    }

    double get_avg_fouls() {
        return total_fouls / games_played;
    }

    double get_overall_score() {
        double weighted_score = (total_points * 0.5) + (total_rebounds * 0.3) +
            (total_assists * 0.2) - (total_fouls * 0.2);
        return weighted_score / games_played;
    }

    // tmbh game stats baru
    void add_game_stats(int points, int rebounds, int assists, int fouls) {
        games_played++;
        total_points += points;
        total_rebounds += rebounds;
        total_assists += assists;
        total_fouls += fouls;
    }
};

// bwt manage players
class PlayerManager {
public:
    Player** player_array;
    int size;
    int capacity;

    PlayerManager() {
        capacity = INITIAL_CAPACITY;
        size = 0;
        player_array = new Player * [capacity];
    }

    void add_player(Player* player) {
        player_array[size++] = player;
    }

    // cari player based on nama n id
    Player* find_player(const char* name, int team_id) {
        for (int i = 0; i < size; i++) {
            if (strcmp(player_array[i]->name, name) == 0 &&
                player_array[i]->team_id == team_id) {
                return player_array[i];
            }
        }
        return nullptr;
    }

    int get_size() { return size; }
    Player* get_player(int index) { return player_array[index]; }
    Player** get_array() { return player_array; }
};

// bwt team-based statistics
struct Team {
    int id;
    Player** members;
    int member_count;
    int capacity;
    double avg_performance;

    Team(int team_id) : id(team_id), member_count(0), capacity(8), avg_performance(0) {
        members = new Player * [capacity];
    }

    void add_player(Player* player) {
        if (member_count >= capacity) {
            capacity *= 2;
            Player** new_members = new Player * [capacity];
            for (int i = 0; i < member_count; i++) {
                new_members[i] = members[i];
            }
            members = new_members;
        }
        members[member_count++] = player;
    }

    // avg performance tim
    void calculate_avg_performance() {
        double total_perf = 0;
        int count = 0;

        for (int i = 0; i < member_count; i++) {
            if (members[i]->games_played > 0) {
                total_perf += members[i]->get_overall_score();
                count++;
            }
        }

        avg_performance = total_perf / count;
    }
};

// bwt handle smw teams
class TeamManager {
public:
    Team** team_array;
    int size;
    int capacity;

    TeamManager() : size(0), capacity(8) {
        team_array = new Team * [capacity];
    }

    // cari team yang dh ada or bwt yang baru
    Team* find_or_create_team(int team_id) {
        // coba cari existing team dulu
        for (int i = 0; i < size; i++) {
            if (team_array[i]->id == team_id) {
                return team_array[i];
            }
        }

        // bt team baru klo blm ad
        if (size >= capacity) {
            capacity *= 2;
            Team** new_array = new Team * [capacity];
            for (int i = 0; i < size; i++) {
                new_array[i] = team_array[i];
            }
            team_array = new_array;
        }

        team_array[size] = new Team(team_id);
        return team_array[size++];
    }

    int get_size() { return size; }
    Team** get_array() { return team_array; }
};

template<typename T>
int partition(T* arr[], int low, int high, bool (*compare_fn)(T*, T*)) {
    int mid = low + (high - low) / 2;
    T* pivot = arr[mid];

    while (low <= high) {
        while (compare_fn(arr[low], pivot)) low++;
        while (compare_fn(pivot, arr[high])) high--;

        if (low <= high) {
            swap(arr[low], arr[high]);
            low++;
            high--;
        }
    }
    return low;
}

template<typename T>
void quick_sort(T* arr[], int low, int high, bool (*compare_fn)(T*, T*)) {
    if (low < high) {
        int partition_idx = partition(arr, low, high, compare_fn);
        quick_sort(arr, low, partition_idx - 1, compare_fn);
        quick_sort(arr, partition_idx, high, compare_fn);
    }
}

// comparison fx
bool compare_by_overall(Player* a, Player* b) {
    double score_a = a->get_overall_score();
    double score_b = b->get_overall_score();

    if (!is_nearly_equal(score_a, score_b)) {
        return score_a > score_b;
    }
    return strcmp(a->name, b->name) < 0;
}

bool compare_by_points(Player* a, Player* b) {
    double avg_a = a->get_avg_points();
    double avg_b = b->get_avg_points();

    if (!is_nearly_equal(avg_a, avg_b)) {
        return avg_a > avg_b;
    }
    return strcmp(a->name, b->name) < 0;
}

bool compare_by_rebounds(Player* a, Player* b) {
    double avg_a = a->get_avg_rebounds();
    double avg_b = b->get_avg_rebounds();

    if (!is_nearly_equal(avg_a, avg_b)) {
        return avg_a > avg_b;
    }
    return strcmp(a->name, b->name) < 0;
}

bool compare_by_assists(Player* a, Player* b) {
    double avg_a = a->get_avg_assists();
    double avg_b = b->get_avg_assists();

    if (!is_nearly_equal(avg_a, avg_b)) {
        return avg_a > avg_b;
    }
    return strcmp(a->name, b->name) < 0;
}

bool compare_by_fewest_fouls(Player* a, Player* b) {
    double avg_a = a->get_avg_fouls();
    double avg_b = b->get_avg_fouls();

    if (!is_nearly_equal(avg_a, avg_b)) {
        return avg_a < avg_b;  // fouls 
    }
    return strcmp(a->name, b->name) < 0;
}

bool compare_teams_by_performance(Team* a, Team* b) {
    if (!is_nearly_equal(a->avg_performance, b->avg_performance)) {
        return a->avg_performance > b->avg_performance;
    }
    return a->id < b->id;
}

// bwt print max top 3 players
void print_top_players(Player** players, int count, const char* command) {
    int top_count = min(3, count);
    cout << fixed << setprecision(2);

    for (int i = 0; i < top_count; i++) {
        cout << players[i]->name << " ";

        if (strcmp(command, "All") == 0) {
            cout << players[i]->get_overall_score();
        }
        else if (strcmp(command, "Score") == 0) {
            cout << players[i]->get_avg_points();
        }
        else if (strcmp(command, "Rebound") == 0) {
            cout << players[i]->get_avg_rebounds();
        }
        else if (strcmp(command, "Assist") == 0) {
            cout << players[i]->get_avg_assists();
        }
        else if (strcmp(command, "Foul") == 0) {
            cout << players[i]->get_avg_fouls();
        }

        cout << endl;
    }
}

int main() {
    int total_commands;
    if (!(cin >> total_commands)) {
        return 0;
    }

    PlayerManager player_mgr;

    for (int i = 0; i < total_commands; i++) {
        char command[16];
        cin >> command;

        if (strcmp(command, "Play") == 0) {
            char player_name[MAX_NAME_LEN];
            int team_id, points, rebounds, assists, fouls;

            cin >> player_name >> team_id >> points >> rebounds >> assists >> fouls;

            Player* player = player_mgr.find_player(player_name, team_id);
            if (player == nullptr) {
                player = new Player(player_name, team_id);
                player_mgr.add_player(player);
            }

            player->add_game_stats(points, rebounds, assists, fouls);

        }
        else if (player_mgr.get_size() > 0) {

            if (strcmp(command, "Team") == 0) {
                TeamManager team_mgr;

                // group players based on team
                for (int j = 0; j < player_mgr.get_size(); j++) {
                    Player* current_player = player_mgr.get_player(j);
                    if (current_player->games_played > 0) {
                        Team* team = team_mgr.find_or_create_team(current_player->team_id);
                        team->add_player(current_player);
                    }
                }

                // itung avg team
                for (int j = 0; j < team_mgr.get_size(); j++) {
                    team_mgr.get_array()[j]->calculate_avg_performance();
                }

                // sort team based on perf
                quick_sort<Team>(team_mgr.get_array(), 0, team_mgr.get_size() - 1,
                    compare_teams_by_performance);

                // print top 3 teams
                int top_teams = min(3, team_mgr.get_size());
                cout << fixed << setprecision(2);
                for (int j = 0; j < top_teams; j++) {
                    cout << team_mgr.get_array()[j]->id << " "
                        << team_mgr.get_array()[j]->avg_performance << endl;
                }

            }
            else {
                // temp array bwt sorting players
                Player** temp_players = new Player * [player_mgr.get_size()];
                for (int j = 0; j < player_mgr.get_size(); j++) {
                    temp_players[j] = player_mgr.get_player(j);
                }

                if (strcmp(command, "All") == 0) {
                    quick_sort<Player>(temp_players, 0, player_mgr.get_size() - 1, compare_by_overall);
                }
                else if (strcmp(command, "Score") == 0) {
                    quick_sort<Player>(temp_players, 0, player_mgr.get_size() - 1, compare_by_points);
                }
                else if (strcmp(command, "Rebound") == 0) {
                    quick_sort<Player>(temp_players, 0, player_mgr.get_size() - 1, compare_by_rebounds);
                }
                else if (strcmp(command, "Assist") == 0) {
                    quick_sort<Player>(temp_players, 0, player_mgr.get_size() - 1, compare_by_assists);
                }
                else if (strcmp(command, "Foul") == 0) {
                    quick_sort<Player>(temp_players, 0, player_mgr.get_size() - 1, compare_by_fewest_fouls);
                }

                print_top_players(temp_players, player_mgr.get_size(), command);
            }
        }
    }

    return 0;
}