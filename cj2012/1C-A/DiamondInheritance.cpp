#include <everything.h>

using namespace std;

string read_solve_case() {
    u32 N;
    cin >> N;
    vector<vector<u32>> graph(N);
    for (u32 i = 0; i < N; ++i) {
        u32 M;
        cin >> M;
        graph[i].reserve(M);
        for (u32 j = 0; j < M; ++j) {
            u32 succ;
            cin >> succ;
            graph[i].push_back(succ-1);
        }
    }
    for (u32 i = 0; i < N; ++i) {
        vector<u32> reach_counts(N, 0);
        vector<u32> stack(1, i);
        while (!stack.empty()) {
            u32 v = stack.back();
            stack.pop_back();
            if (++reach_counts[v] > 1)
                return "Yes";
            stack.insert(stack.end(), graph[v].begin(), graph[v].end());
        }
    }
    return "No";
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

