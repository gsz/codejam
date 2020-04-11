#include <iostream>
#include <algorithm>
#include <tuple>
#include <string>
#include <vector>

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

using namespace std;

string read_solve_case() {
    u32 N;
    cin >> N;
    vector<tuple<u32,u32,u32>> activities(N);
    for (u32 i = 0; i < N; ++i) {
        u32 Si, Ei;
        cin >> Si >> Ei;
        activities[i] = make_tuple(Si, Ei, i);
    }
    sort(activities.begin(), activities.end());
    string schedule(N, '*');
    u32 Cbusy_until{0}, Jbusy_until{0};
    for (auto &evt : activities) {
        u32 S, E, i;
        tie(S, E, i) = evt;
        if (Cbusy_until <= S) {
            Cbusy_until = E;
            schedule[i] = 'C';
        } else if (Jbusy_until <= S) {
            Jbusy_until = E;
            schedule[i] = 'J';
        } else {
            return "IMPOSSIBLE";
        }
    }
    return schedule;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl;
    }
    return 0;
}
