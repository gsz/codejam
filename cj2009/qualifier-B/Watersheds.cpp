#include <everything.h>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

pair<int,int> flow_successor(pair<int,int> point, vector<vector<int>> &alts) {
    int y = point.first, x = point.second;
    pair<int,int> target;
    int lowest_alt = alts[y][x];
    vector<pair<int,int>> candidates = {{y+1, x}, {y, x+1}, 
                                        {y, x-1}, {y-1, x}};
    for (auto &cy_cx : candidates) {
        int cy, cx;
        tie(cy, cx) = cy_cx;
        if (cy < 0 || cy >= (int)(alts.size())
                || cx < 0 || cx >= (int)(alts[y].size()))
            continue;
        if (alts[cy][cx] <= lowest_alt) {
            lowest_alt = alts[cy][cx];
            target = make_pair(cy, cx);
        }
    }
    target = (lowest_alt < alts[y][x] ? target : point);
    return target;
}

void read_solve_print_case() {
    int H, W;
    cin >> H >> W;
    vector<vector<int>> alts(H, vector<int>(W));
    for (int y = 0; y < H; ++y)
        for (int x = 0; x < W; ++x)
            cin >> alts[y][x];
    vector<vector<int>> basins(H, vector<int>(W, -1));
    int seen_basins = 0;
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            pair<int,int> pos = make_pair(y, x);
            vector<pair<int,int>> path;
            while (basins[pos.first][pos.second] == -1) {
                path.push_back(pos);
                pair<int,int> next = flow_successor(pos, alts);
                if (next == pos)
                    basins[next.first][next.second] = seen_basins++;
                pos = next;
            }
            for (auto &yx : path)
                basins[yx.first][yx.second] = basins[pos.first][pos.second];
        }
    }
    for (auto &row : basins) {
        for (int b : row)
            cout << (char)('a' + b) << ' ';
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << endl;
        read_solve_print_case();
    }
    return 0;
}
