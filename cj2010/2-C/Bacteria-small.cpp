#include <everything.h>

using namespace std;

int read_solve_case() {
    int R;
    cin >> R;
    array<array<bool, 101>, 101> grid;
    for (auto &row : grid)
        row.fill(false);
    for (int r = 0; r < R; ++r) {
        int X1, Y1, X2, Y2;
        cin >> X1 >> Y1 >> X2 >> Y2;
        for (int y = Y1; y <= Y2; ++y)
            for (int x = X1; x <= X2; ++x)
                grid[y][x] = true;
    }
    bool finished = false;
    array<array<bool, 101>, 101> grid2;
    for (auto &row : grid2)
        row.fill(false);
    int turns = 0;
    while (!finished) {
        turns += 1;
        finished = true;
        for (int y = 1; y <= 100; ++y) {
            for (int x = 1; x <= 100; ++x) {
                grid2[y][x] = ((grid[y][x] && (grid[y-1][x] || grid[y][x-1]))
                               || (grid[y-1][x] && grid[y][x-1]));
                if (grid2[y][x])
                    finished = false;
            }
        }
        swap(grid, grid2);
    }
    return turns;
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
