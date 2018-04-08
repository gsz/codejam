#include <cmath>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

void solve_case_interactive() {
    int A;
    cin >> A;
    int w, h = static_cast<int>(ceil(sqrt(A)));
    w = (h * (h-1) >= A ? h-1 : h);
    h = max(h, 3);
    w = max(w, 3);
    vector<vector<bool>> rect(h + 1, vector<bool>(w + 1, false));
    vector<vector<int>> neighbors(h + 1, vector<int>(w + 1, 9));
    set<tuple<int,int,int>> positions;
    for (int i = 2; i < h; ++i) {
        for (int j = 2; j < w; ++j) {
            positions.insert(make_tuple(9, i, j));
        }
    }
    while (true) {
        int si, sj;
        tie(ignore, si, sj) = *positions.rbegin();
        cout << si << ' ' << sj << endl;
        int ri, rj;
        cin >> ri >> rj;
        if (ri == 0 || rj == 0)
            return;
        if (ri == -1 || rj == -1)
            exit(0);
        if (rect[ri][rj] == true)
            continue;
        rect[ri][rj] = true;
        for (int i = max(ri-1, 2); i < min(ri+2, h); ++i) {
            for (int j = max(rj-1, 2); j < min(rj+2, w); ++j) {
                positions.erase(make_tuple(neighbors[i][j], i, j));
                neighbors[i][j] -= 1;
                positions.insert(make_tuple(neighbors[i][j], i, j));
            }
        }
    }
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        solve_case_interactive();
    }
    return 0;
}
