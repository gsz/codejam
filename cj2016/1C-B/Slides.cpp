#include <cassert>
#include <limits>
#include <memory>
#include <ios>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

typedef vector<vector<bool>> Graph;

Graph read_solve_case() {
    u64 B, M;
    cin >> B >> M;
    if (M > 1ull << (B-2)) {
        return Graph(); }
    Graph G;
    for (u64 i = 0; i < B; ++i) {
        G.emplace_back(B, false); }
    for (u64 i = 1; i < B-1; ++i) {
        for (u64 j = i+1; j < B; ++j) {
            G[i][j] = true; }
    }
    if (M == 1ull << (B-2)) {
        for (u64 i = 1; i < B; ++i) {
            G[0][i] = true; }
        return G;
    }
    for (u64 i = 0; i < B-2; ++i) {
        G[0][B-2-i] = (M >> i) & 1; }
    return G;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        Graph G = read_solve_case();
        cout << "Case #" << ci << ": ";
        if (G.size() == 0) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << "POSSIBLE" << endl;
            for (size_t i = 0; i < G.size(); ++i) {
                for (size_t j = 0; j < G[i].size(); ++j) {
                    cout << (int)G[i][j]; }
                cout << endl;
            }
        }
    }
    return 0;
}

