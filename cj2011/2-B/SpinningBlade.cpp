#include <everything.h>

using namespace std;

struct Instance {
    int R, C, D;
    vector<vector<int>> mass, cumulative;

    void read();
    int rect_mass(int r1, int c1, int r2, int c2);
    int solve();
};

void Instance::read() {
    cin >> R >> C >> D;
    mass = vector<vector<int>>(R, vector<int>(C));
    cumulative = vector<vector<int>>(R+1, vector<int>(C+1, 0));
    for (int r = 0; r < R; ++r) {
        string row;
        cin >> row;
        for (int c = 0; c < C; ++c)
            mass[r][c] = row[c] - '0';
    }
    for (int r = 1; r <= R; ++r) {
        vector<int> row_cumulative(C+1, 0);
        for (int c = 1; c <= C; ++c) {
            row_cumulative[c] = mass[r-1][c-1] + row_cumulative[c-1];
            cumulative[r][c] = row_cumulative[c] + cumulative[r-1][c];
        }
    }
}

int Instance::rect_mass(int r1, int c1, int r2, int c2) {
    r2 += 1;
    c2 += 1;
    return (cumulative[r2][c2] + cumulative[r1][c1]
            - cumulative[r2][c1] - cumulative[r1][c2]);
}

int Instance::solve() {
    int max_size = -1;
    for (int size = 3; size <= min(R, C); ++size) {
        vector<int> vert_imbalances(C - size + 1, 0);
        for (int c = 0; c <= C - size; ++c) {
            int factor = -(size - 1);
            for (int r = 0; r < size / 2; ++r, factor += 2)
                vert_imbalances[c] += factor * rect_mass(r, c, r, c+size-1);
            if (size % 2 != 0)
                factor += 2;
            for (int r = (size + 1) / 2; r < size; ++r, factor += 2)
                vert_imbalances[c] += factor * rect_mass(r, c, r, c+size-1);
        }
        for (int r = 0; r <= R - size; ++r) {
            int horiz_imbalance = 0;
            int factor = -(size - 1);
            for (int c = 0; c < size / 2; ++c, factor += 2)
                horiz_imbalance += factor * rect_mass(r, c, r+size-1, c);
            if (size %2 != 0)
                factor += 2;
            for (int c = (size + 1) / 2; c < size; ++c, factor += 2)
                horiz_imbalance += factor * rect_mass(r, c, r+size-1, c);
            for (int c = 0; c <= C - size; ++c) {
                int ul = mass[r][c], ur = mass[r][c+size-1];
                int ll = mass[r+size-1][c], lr = mass[r+size-1][c+size-1];
                int himb = horiz_imbalance + (size-1) * (ul + ll - ur - lr);
                int vimb = vert_imbalances[c] + (size-1) * (ul + ur - ll - lr);
                if (himb == 0 && vimb == 0) {
                    max_size = size;
                    goto sizeloop_continue;
                }
                if (c < C - size) {
                    horiz_imbalance += 
                        (size-1) * rect_mass(r, c, r+size-1, c);
                    horiz_imbalance += 
                        (size-1) * rect_mass(r, c+size, r+size-1, c+size);
                    horiz_imbalance -=
                        2 * rect_mass(r, c+1, r+size-1, c+size-1); 
                }
            }
            if (r < R - size) {
                for (int c = 0; c <= C - size; ++c) {
                    vert_imbalances[c] += 
                        (size-1) * rect_mass(r, c, r, c+size-1);
                    vert_imbalances[c] +=
                        (size-1) * rect_mass(r+size, c, r+size, c+size-1);
                    vert_imbalances[c] -=
                        2 * rect_mass(r+1, c, r+size-1, c+size-1);
                }
            }
        }
sizeloop_continue: ;
    }
    return max_size;
}

string read_solve_case() {
    Instance inst;
    inst.read();
    int result = inst.solve();
    return (result == -1 ? "IMPOSSIBLE" : to_string(result));
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
