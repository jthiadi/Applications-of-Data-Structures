#include "function.h"
using namespace std;


#ifdef LOCAL_TEST
int main() {
    int N, G;
    cin >> N >> G;
    vector<Team> teams(N);

    //step 1: input teams & game results
    /*......*/

    //step 2: determine rules (retro or not)
    /*......*/

    //step 3: sorting
    /*......*/

    //step 4: output
    for (int i = 0; i < teams.size() ; i++) {
        cout<< i+1 << ". "<< teams[i].name << " " << teams[i].win << "-" << teams[i].loss << endl;
    }
}
#endif