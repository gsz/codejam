#include <cassert>
#include <memory>
#include <ios>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

typedef unsigned int uint;

typedef vector<vector<bool>> grid;

grid filled_grid(uint R, uint C) {
    grid result;
    for (uint r = 0; r < R; ++r) {
        result.emplace_back(C, true);
    }
    return result;
}

int filled_neighbors(grid &g, uint r, uint c) {
    uint R = g.size(), C = g[0].size();
    int result = 0;
    if (r > 0) { result += g[r-1][c]; }
    if (c > 0) { result += g[r][c-1]; }
    if (r < R-1) { result += g[r+1][c]; }
    if (c < C-1) { result += g[r][c+1]; }
    return result;
}

void advance(grid& g, uint& r, uint& c) {
    c += 1;
    if (c >= g[0].size()) {
        c = 0;
        r+= 1;
    }
}

bool in_bounds(grid& g, uint r, uint c) {
    return r < g.size() && c < g[0].size();
}

int liberate(grid &g, int empty_N, bool delayfirst) {
    uint unhappiness_reduction = 0;
    uint r, c;
    r = c = 0;
    if (delayfirst) {
        while (in_bounds(g, r, c) && filled_neighbors(g, r, c) < 4) { 
            advance(g, r, c); }
        advance(g, r, c);
    }
    for ( ; in_bounds(g, r, c) && empty_N > 0; advance(g, r, c)) { 
        if (filled_neighbors(g, r, c) == 4) {
            g[r][c] = false;
            empty_N -= 1;
            unhappiness_reduction += 4;
        }
    }
    for (int neighbors = 3; neighbors > 0; --neighbors) {
        for (r = c = 0; in_bounds(g, r, c) && empty_N > 0; advance(g, r, c)) {
            if (filled_neighbors(g, r, c) == neighbors) {
                g[r][c] = false;
                unhappiness_reduction += neighbors;
                empty_N -= 1;
            }
        } 
    }
    return unhappiness_reduction;
}

int read_solve_case() {
    uint R, C, N;
    cin >> R >> C >> N;
    grid g = filled_grid(R, C);
    int pain1 = R*C*2 - R - C - liberate(g, R*C - N, false);
    g = filled_grid(R, C);
    int pain2 = R*C*2 - R - C - liberate(g, R*C - N, true);
    return min(pain1, pain2);
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl; }
    return 0;
}

