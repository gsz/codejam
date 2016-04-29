#include <cassert>
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

string read_solve_case() {
    int R, C;
    cin >> R >> C;
    vector<int> num_arrows_in_col(C, 0);
    vector<int> num_arrows_in_row;
    vector<int> final_downward_arrow_in_col(C, -1);
    vector<pair<int, int>> bad_arrows;
    for (int y = 0; y < R; ++y) {
        string row;
        cin >> row;
        int num_arrs = 0;
        int final_rightward_arrow = -1;
        for (int x = 0; x < C; ++x) {
            if (row[x] == '.') {
                continue; }
            if ((row[x] == '<' && num_arrs == 0) ||
                    (row[x] == '^' && num_arrows_in_col[x] == 0)) {
                bad_arrows.emplace_back(y, x); 
            }
            final_rightward_arrow = final_downward_arrow_in_col[x] = -1;
            if (row[x] == '>') {
                final_rightward_arrow = x; 
            } else if (row[x] == 'v') {
                final_downward_arrow_in_col[x] = y; 
            }
            num_arrows_in_col[x] += 1;
            num_arrs += 1;
        }
        if (final_rightward_arrow != -1) {
            bad_arrows.emplace_back(y, final_rightward_arrow); }
        num_arrows_in_row.push_back(num_arrs);
    }
    for (int x = 0; x < C; ++x) {
        if (final_downward_arrow_in_col[x] != -1) {
            bad_arrows.emplace_back(final_downward_arrow_in_col[x], x); }
    }
    for (auto arr : bad_arrows) {
        if (num_arrows_in_row[arr.first] == 1 && 
                num_arrows_in_col[arr.second] == 1) {
            return "IMPOSSIBLE"; }
    }
    return to_string(bad_arrows.size());
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

