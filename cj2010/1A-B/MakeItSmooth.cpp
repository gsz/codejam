#include <everything.h>

using namespace std;

const int MAX_NUM = 255;
const int DEL_ALL = MAX_NUM+1;

int fill_cost(int j, int k, int M, int I) {
    return j == k ? 0 : (abs(j - k) - 1) / M * I;
}

int read_solve_case() {
    int D, I, M, N;
    cin >> D >> I >> M >> N;
    vector<int> pixels(N);
    for (int i = 0; i < N; ++i)
        cin >> pixels[i];
    vector<vector<int>> costs(N, vector<int>(DEL_ALL+1));
    costs[0][DEL_ALL] = D;
    for (int j = 0; j < DEL_ALL; ++j)
        costs[0][j] = abs(pixels[0] - j);
    for (int i = 1; i < N; ++i) {
        costs[i][DEL_ALL] = costs[i-1][DEL_ALL] + D;
        for (int j = 0; j < DEL_ALL; ++j) {
            int change_cost = costs[i-1][DEL_ALL];
            if (M > 0) {
                for (int k = 0; k < DEL_ALL; ++k) {
                    int newcost = costs[i-1][k] + fill_cost(j, k, M, I);
                    change_cost = min(change_cost, newcost);
                }
            } else {
                change_cost = min(change_cost, costs[i-1][j]);
            }
            change_cost += abs(pixels[i] - j);
            costs[i][j] = min(change_cost, D + costs[i-1][j]);
        }
    }
    int min_cost = INT_MAX;
    for (int j = 0; j <= DEL_ALL; ++j)
        min_cost = min(min_cost, costs[N-1][j]);
    return min_cost;
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
