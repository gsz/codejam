#include <everything.h>

using namespace std;

/* Times in deciseconds, heights in centimeters */
const int DRAIN_RATE = 1;
const int MIN_PASSABLE_GAP = 50;
const int MIN_KAYAKABLE_WATER = 20;
const int KAYAK_TIME = 10;
const int DRAG_TIME = 100;

struct Instance {
    int H, N, M;
    vector<vector<int>> ceils;
    vector<vector<int>> floors;
    bool in_bounds(int y, int x) const { 
        return y >= 0 && y < N && x >= 0 && x < M; 
    }
    int earliest_passable(int y1, int x1, int y2, int x2) const;
    int pass_time(int y1, int x1, int y2, int x2, int t) const;
    void read();
    int earliest_leave_from(int y, int x, int starttime) const;
    int solve() const; 
};

int Instance::earliest_passable(int y1, int x1, int y2, int x2) const { 
    int gap = (min(ceils[y2][x2], ceils[y1][x1]) - 
               max(floors[y2][x2], floors[y1][x1]));
    if (gap < MIN_PASSABLE_GAP)
        return INT_MAX;
    int wait = 50 + H - ceils[y2][x2] * DRAIN_RATE;
    return (wait > 0 ? wait : INT_MIN);
}

int Instance::pass_time(int y1, int x1, int y2, int x2, int t) const {
    t = max(t, earliest_passable(y1, x1, y2, x2));
    if (t == INT_MAX)
        return INT_MAX;
    if (H - max(0, t) * DRAIN_RATE >= floors[y1][x1] + MIN_KAYAKABLE_WATER) {
        t += KAYAK_TIME;
    } else {
        t += DRAG_TIME;
    }
    return t;
}

void Instance::read() {
    Instance inst;
    cin >> H >> N >> M;
    ceils.resize(N);
    floors.resize(N);
    for (int y = 0; y < N; ++y) {
        ceils[y].resize(M);
        floors[y].resize(M);
    }
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < M; ++x) {
            cin >> ceils[y][x];
        }
    }
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < M; ++x) {
            cin >> floors[y][x];
        }
    }
}

int Instance::earliest_leave_from(int y, int x, int starttime) const {
    vector<vector<int>> earliest_arrival(N, vector<int>(M, INT_MAX));
    vector<vector<bool>> processed(N, vector<bool>(M, false));
    priority_queue<tuple<int,int,int>,
                   vector<tuple<int,int,int>>,
                   greater<tuple<int,int,int>>> q;
    q.emplace(starttime, y, x);
    while (!q.empty()) {
        int t, y, x;
        tie(t, y, x) = q.top();
        q.pop();
        if (processed[y][x])
            continue;
        processed[y][x] = true;
        for (int ny = y-1; ny < y+2; ++ny) {
            for (int nx = x - (ny == y); nx < x+2; nx += 2) {
                if (!in_bounds(ny, nx) || processed[ny][nx])
                    continue;
                int nt = pass_time(y, x, ny, nx, t);
                if (nt >= earliest_arrival[ny][nx])
                    continue;
                earliest_arrival[ny][nx] = nt;
                q.emplace(nt, ny, nx);
            }
        }
    }
    return earliest_arrival[N-1][M-1];
}

int Instance::solve() const {
    return max(0, earliest_leave_from(0, 0, INT_MIN));
}

double read_solve_case() {
    Instance inst;
    inst.read();
    return static_cast<double>(inst.solve()) / 10;
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
