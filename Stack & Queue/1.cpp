#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int quit_time = 60;

class family {
public:
    int id;
    int fam_num;
    int fee;
    int arrival_time;
    //bool gogo;
    bool special_fam;

    family() {
        id = 0;
        fam_num = 0;
        fee = 0;
        arrival_time = 0;
        //gogo = false;
        special_fam = false;
    }
};

class queue {
public:
    family* q;
    int head, tail;
    int total_count;
    int next_fam_id;
    queue* queues;
    int money_collected, total_people, current_queue, total_quit;
    int reg_count;

    int entered_id[10000];
    int entered_num[10000];
    int entered_index;

    queue() {
        q = new family[10000];
        head = 0;
        tail = -1;
        total_count = 0;
        next_fam_id = 1;

        money_collected = 0;
        total_people = 0;
        current_queue = 0;
        total_quit = 0;
        reg_count = 0;
        entered_index = 0;
    }

    bool special(int Y) {
        if (total_count <= 1 || Y == -1) return false;

        int fee_sum = 0;
        for (int i = tail - 1; i >= head; --i) {
            fee_sum += q[i].fee;
            if (fee_sum > Y) break;
            if (fee_sum == Y) {
                bool any_special = false;
                for (int j = i; j <= tail - 1; ++j) {
                    if (q[j].special_fam) {
                        any_special = true;
                        break;
                    }
                }
                if (!any_special) return true;
            }
        }
        return false;

    }

    void remove_front() {
        current_queue -= q[head].fam_num;
        head++;
        total_count--;
    }

    void enqueue(int size, int fee, int minute, int Y) {
        if (total_count >= 10000) return;

        tail++;
        q[tail].id = next_fam_id++;
        q[tail].fam_num = size;
        q[tail].fee = fee;
        q[tail].arrival_time = minute;
        q[tail].special_fam = false;

        total_count++;
        current_queue += size;

        if (special(Y)) {
            q[tail].special_fam = true;
            q[tail].fee = 0;
            //cout << "famid" << q[tail].id << "special" << endl;

        }
        //cout << "famid:" << q[tail].id << " total " << size << "fee" << fee << "di menit" << minute << endl;

    }

    void registration() {
        if (total_count == 0) return;

        reg_count++;
        if (reg_count % 2 == 0) {
            money_collected += q[head].fee;
            total_people += q[head].fam_num;

            entered_id[entered_index] = q[head].id;
            entered_num[entered_index] = q[head].fam_num;
            entered_index++;
            //cout << "registered" << q[head].id << "people" << q[head].fam_num << "fee" << q[head].fee << endl;

            remove_front();
        }

    }

    void times_up(int X, int current_minute) {
        int i = tail;
        int masuk = 0;

        while ((total_count - masuk - 1) > X) {
            if (q[i].fam_num >= 100) {
                i--;
                masuk++;
                continue;
            }

            if ((current_minute - q[i].arrival_time >= quit_time) && !q[i].special_fam) {
                total_quit += q[i].fam_num;
                current_queue -= q[i].fam_num;
                i--;
                masuk++;
            }
            else {
                break;
            }
        }

        if (masuk > 0) {
            tail -= masuk;
            total_count -= masuk;
        }
    }

    void print_summary(int index) {
        cout << "Place " << index << " Summary" << endl;
        cout << "Total Money: " << money_collected << endl;
        cout << "Total People Entered: " << total_people << endl;
        cout << "Total People Quit: " << total_quit << endl;
        cout << "Current People Queuing: " << current_queue << "\n\n";
        cout << "Entered Families :" << endl;
        for (int i = entered_index - 1; i >= 0; --i) {
            cout << "Family " << entered_id[i] << " with " << entered_num[i] << " people" << endl;
        }
        cout << endl;
    }
};

int main() {
    int F, X, Y, M;
    cin >> F >> X >> Y >> M;
    cin.ignore();
    queue* queues = new queue[F];

    //queue queues[100]; 
    string line;

    for (int minute = 0; minute <= M; minute++) {
        //cout << "menit" << minute << "----------" << endl;

        for (int i = 0; i < F; i++) {
            getline(cin, line);

            if (line == "") {
                i--;
                continue;
            }

            queues[i].registration();
            queues[i].times_up(X, minute);

            if (line == "0") continue;

            stringstream ss(line);
            int A, P;
            char c;

            while (ss >> A >> c >> P) {
                queues[i].enqueue(A, P, minute, Y);
            }
        }
    }

    for (int i = 0; i < F; i++) {
        queues[i].print_summary(i);
    }

    return 0;
}
