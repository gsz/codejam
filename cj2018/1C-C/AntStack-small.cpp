#include <climits>
#include <iostream>
#include <vector>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

int read_solve_case() {
    int N;
    cin >> N;
    vector<int> W(N);
    for (int i = 0; i < N; ++i)
        cin >> W[i];
    vector<vector<int>> best_weight(N, vector<int>(N+1, INT_MAX));
    for (int i = 0; i < N; ++i)
        best_weight[i][0] = 0;
    int bestlen = 1;
    best_weight[0][1] = W[0];
    for (int i = 1; i < N; ++i) {
        for (int l = 1; l <= i+1; ++l) {
            int skipped_weight = best_weight[i-1][l];
            int extended_weight = INT_MAX;
            if (best_weight[i-1][l-1] != INT_MAX && 
                    best_weight[i-1][l-1] <= 6 * W[i]) {
                extended_weight = best_weight[i-1][l-1] + W[i];
            }
            best_weight[i][l] = min(skipped_weight, extended_weight);
            if (best_weight[i][l] != INT_MAX && l > bestlen)
                bestlen = l;
        }
    }
    return bestlen;
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
