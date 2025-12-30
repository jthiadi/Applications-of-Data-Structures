//progres: udh add save cursor sisa reverse 7/10

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct song {
    string name;
    song* next_song;
};

class playlist {
public:
    song* first_song;
    song* last_song;

    playlist() : first_song(0), last_song(0) {}

    void add_song_end(string songs) {
        //cout << "nama lagunya" << songs << endl;

        song* new_song = new song;

        new_song->name = songs;
        new_song->next_song = 0;

        if (first_song) {
            last_song->next_song = new_song;
            last_song = new_song;
        }
        else {
            first_song = new_song;
            last_song = new_song;
        }
    }

    void put_song(int position, string& song_name) {
        song* new_song = new song;
        new_song->name = song_name;
        new_song->next_song = 0;

        song dummy;
        dummy.next_song = first_song;
        song* current = &dummy;

        for (int i = 1; i < position; i++) {
            current = current->next_song;
        }

        new_song->next_song = current->next_song;
        current->next_song = new_song;

        first_song = dummy.next_song;
        if (!new_song->next_song) {
            last_song = new_song;
        }
    }

    string hapus(int position) {
        song dummy;
        dummy.next_song = first_song;
        song* prev = &dummy;

        for (int i = 1; i < position; i++) {
            prev = prev->next_song;
        }

        song* remove = prev->next_song;
        string song_name = remove->name;
        prev->next_song = remove->next_song;

        first_song = dummy.next_song;
        if (remove == last_song) {
            last_song = (first_song == remove) ? 0 : prev;
        }

        return song_name;
    }

    void shift(int p, int i, char d) {
        string song = hapus(p);
        if (d == 'L') {
            int position = p - i;
            if (position < 1) position = 1;
            put_song(position, song);
        }
        else {
            put_song(p + i, song);
        }
    }

    void reverse(int k) {
        if (!first_song || k <= 1) return;

        song* current = first_song;
        song* prev_tail = NULL;
        song* new_head = NULL;

        while (current) {
            song* prev = NULL;
            song* cur = current;
            song* next = NULL;
            song* head = current;

            int count = 0;
            while (cur && count < k) {
                next = cur->next_song;
                cur->next_song = prev;
                prev = cur;
                cur = next;
                count++;
            }

            if (prev_tail) {
                prev_tail->next_song = prev;
            }
            else {
                new_head = prev;
            }

            prev_tail = head;
            current = cur;
        }

        if (new_head) {
            first_song = new_head;
        }
        last_song = prev_tail;
    }

    void print_output(int ls) {
        if (first_song) {
            cout << "Playlist " << ls << ":" << endl;
            song* current = first_song;
            while (current) {
                cout << "> " << current->name << endl;
                current = current->next_song;
            }
        }
        else {
            cout << "Playlist " << ls << " is empty" << endl;
            return;
        }
    }
};

string what_command(string input, string current_buffer, playlist* all_playlist, int& cursor_position) {
    stringstream ss(input);
    string command;
    ss >> command;

    if (command == "ADD") {
        int ls;
        ss >> ls;
        all_playlist[ls].add_song_end(current_buffer);
        current_buffer = "";
        cursor_position = -1;
    }
    else if (command == "SAVE") {
        int ls;
        ss >> ls;
        all_playlist[ls].print_output(ls);
    }

    else if (command == "CURSOR") {
        int i;
        char d;
        ss >> i >> d;
        if (d == 'L') {
            cursor_position -= i;
            if (cursor_position < -1) {
                cursor_position = -1;
            }
        }
        else cursor_position += i;
        
        int max_position = current_buffer.length() - 1;
        if (cursor_position > max_position) cursor_position = max_position;
    }

    else if (command == "MOVE") {
        int ls, p, i;
        char d;
        ss >> ls >> p >> i >> d;
        all_playlist[ls].shift(p, i, d);
    }

    else if (command == "REVERSE") {
        int ls, k;
        ss >> ls >> k;
        if (!all_playlist[ls].first_song) {
            cout << "Playlist " << ls << " is empty" << endl;
        }
        else {
            all_playlist[ls].reverse(k);
        }
    }

    else {
        char typed = input[0];
        current_buffer.insert(cursor_position + 1, 1, typed);
        cursor_position++;
    }

    return current_buffer;
}

int main() {
    int total_playlist;
    cin >> total_playlist;
    cin.ignore();

    playlist* all_playlist = new playlist[total_playlist];
    string current_buffer = "";
    string input;

    int cursor_position = -1;

    while (getline(cin, input)) {
        if (input == "") continue;
        current_buffer = what_command(input, current_buffer, all_playlist, cursor_position);
    }

    return 0;
}