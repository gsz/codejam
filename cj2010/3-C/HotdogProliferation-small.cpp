#include <everything.h>

using namespace std;

u64 read_solve_case() {
    int C;
    cin >> C;
    unordered_map<int, int> corners;
    int sumV = 0;
    for (int i = 0; i < C; ++i) {
        int P, V;
        cin >> P >> V;
        corners[P] = V;
        sumV += V;
    }
    vector<int> crowded_corners(sumV);
    u64 moves = 0;
    while (true) {
        int num_crowded = 0;
        for (auto &p_v : corners) {
            if (p_v.second > 1)
                crowded_corners[num_crowded++] = p_v.first;
        }
        if (num_crowded == 0)
            break;
        for (int i = 0; i < num_crowded; ++i) {
            int p = crowded_corners[i];
            moves += corners[p] / 2;
            corners[p-1] = corners[p-1] + corners[p] / 2;
            corners[p+1] = corners[p+1] + corners[p] / 2;
            corners[p] = corners[p] % 2;
            if (corners[p] == 0)
                corners.erase(p);
        }
    }
    return moves;
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
