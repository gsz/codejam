#include <iostream>
#include <vector>

using namespace std;

const int MAX_PILE = 1000;

int solve_case(vector<int> &plates) {
    int needed_cuts[MAX_PILE+1];
    for (int i = 1; i <= MAX_PILE; ++i) {
        needed_cuts[i] = 0;
    }
    int max_height = 0;
    for (auto pi = plates.begin(); pi < plates.end(); ++pi) {
        max_height = max(max_height, *pi);
        for (int eat_time = max_height; eat_time >= 1; --eat_time) {
            needed_cuts[eat_time] += (*pi + eat_time - 1) / eat_time - 1;
        }
    }
    int best_time = MAX_PILE;
    for (int eat_time = 1; eat_time <= MAX_PILE; ++eat_time) {
        best_time = min(best_time, eat_time + needed_cuts[eat_time]);
    }
    return best_time;
}

int read_solve_case() {
    int D;
    cin >> D;
    vector<int> plates(D);
    for (int i = 0; i < D; ++i) {
        int P;
        cin >> P;
        plates.push_back(P);
    }
    return solve_case(plates);
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T, ci;
    cin >> T;
    for (ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl;
    }
    return 0;
}

