#include <everything.h>

using namespace std;

string read_solve_case() {
    int N;
    cin >> N;
    vector<int> low_req(N), high_req(N), completions(N, 0);
    unordered_set<int> left_undone;
    for (int i = 0; i < N; ++i) {
        left_undone.insert(i);
        cin >> low_req[i] >> high_req[i];
    }
    int moves = 0;
    int stars = 0;
    while (!left_undone.empty()) {
        ++moves;
        int best_candidate = -1;
        int best_high_req = -1;
        for (auto i : left_undone) {
            if (high_req[i] <= stars) {
                best_candidate = i;
                break;
            } 
            if (completions[i] > 0)
                continue;
            if (low_req[i] <= stars && high_req[i] > best_high_req) {
                best_candidate = i;
                best_high_req = high_req[i];
            }
        }
        if (best_candidate == -1) 
            return "Too Bad";
        if (high_req[best_candidate] <= stars) {
            left_undone.erase(best_candidate);
            stars += 2 - completions[best_candidate];
        } else {
            stars += 1;
            completions[best_candidate] = 1;
        }
    }
    return to_string(moves);
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
