#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

struct Song {
    string name;
    int duration;
};

int main() {
    vector<Song> playlist;
    string cmd;

    while (cin >> cmd) {
        if (cmd == "ADD_SONG") {
            string name;
            int d, idx;
            cin >> name >> d >> idx;
            Song s{ name, d };
            if (idx < 0 || idx >= playlist.size())
                playlist.push_back(s);
            else
                playlist.insert(playlist.begin() + idx, s);
        }

        else if (cmd == "DELETE_SONG") {
            string name;
            cin >> name;
            bool found = false;
            for (int i = 0; i < playlist.size(); i++) {
                if (playlist[i].name == name) {
                    playlist.erase(playlist.begin() + i);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Song not found\n";
            }
        }


        else if (cmd == "SKIP") {
            long long S;
            cin >> S;
            auto n = playlist.size();
            if (n > 0) {
                S %= n;
                rotate(playlist.begin(),
                    playlist.begin() + S,
                    playlist.end());
            }
        }

        else if (cmd == "REVERSE") {
            reverse(playlist.begin(), playlist.end());
        }

        else if (cmd == "PLAY") {
            long long t;
            cin >> t;
            if (playlist.empty()) {
                cout << "Currently playing: \n";
            }
            else {
                auto cycle = 0;
                for (auto& s : playlist)
                    cycle += s.duration;

                if (t == 0) {
                    cout << "Currently playing: " << playlist[0].name << "\n";
                    continue;
                }

                auto tt = t % cycle;
                if (tt == 0) tt = cycle;
                auto acc = 0;

                for (auto& s : playlist) {
                    acc += s.duration;
                    if (tt <= acc) {
                        cout << "Currently playing: " << s.name << "\n";
                        break;
                    }
                }
            }
        }

        else if (cmd == "DISPLAY") {
            cout << "Playlist Contents:\n";
            if (playlist.empty()) {
                cout << "-- empty --\n";
            }

            else {
                for (auto& s : playlist) {
                    cout << "> " << s.name << " " << s.duration << " seconds\n";
                }
            }
            auto total = 0;
            for (auto& s : playlist) total += s.duration;
            cout << "Playlist Duration: " << total << " seconds\n";
        }
    }
    return 0;
}