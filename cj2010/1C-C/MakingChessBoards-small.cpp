#include <everything.h>

using namespace std;

int hexdigit(char c) {
    if (isalpha(c)) {
        return 10 + c - 'a';
    } else {
        return c - '0';
    }
}

struct Inst {
    int M, N;
    vector<vector<bool>> board;
    vector<vector<bool>> used;

    int maxsize_at(int m, int n) const;
    void mark_used(int m, int n, int size);
    void read();
    void solve_print();
};

int Inst::maxsize_at(int m, int n) const {
    if (used[m][n])
        return 0;
    bool topleft = board[m][n];
    int maxs = 2;
    for (; m + maxs - 1 < M && n + maxs - 1 < N; ++maxs) {
        for (int m2 = m; m2 < m + maxs; ++m2) {
            if (board[m2][n + maxs - 1] != topleft || used[m2][n + maxs - 1])
                return maxs - 1;
        }
        for (int n2 = n; n2 < n + maxs; ++n2) {
            if (board[m + maxs - 1][n2] != topleft || used[m + maxs - 1][n2])
                return maxs - 1;
        }
    }
    return maxs - 1;
}

void Inst::mark_used(int m, int n, int size) {
    for (int m2 = m; m2 < m + size; ++m2)
        for (int n2 = n; n2 < n + size; ++n2)
            used[m2][n2] = true;
}

void Inst::read() { 
    cin >> M >> N;
    board.resize(M);
    used.resize(M);
    for (int m = 0; m < M; ++m) {
        board[m].resize(N);
        used[m].resize(N, false);
        string rawrow;
        cin >> rawrow;
        for (int n = 0; n < N; n+=4) {
            int dig = hexdigit(rawrow[n/4]);
            board[m][n] = dig & 8;
            board[m][n+1] = dig & 4;
            board[m][n+2] = dig & 2;
            board[m][n+3] = dig & 1;
        }
    }
    // board[m][n] will be true if it fits in a chessboard with white 
    // square at (0,0)
    for (int m = 0; m < M; ++m)
        for (int n = 0; n < N; ++n) 
            board[m][n] = (board[m][n] == ((m + n) % 2 == 0));
}

void Inst::solve_print() {
    vector<int> boards_of_size(max(M, N) + 1, 0);
    int remaining_cells = N * M;
    while (remaining_cells > 0) {
        int best_size = 0;
        int best_m = 0, best_n = 0;
        for (int m = 0; m < M; ++m) {
            for (int n = 0; n < N; ++n) {
                int maxs = maxsize_at(m, n);
                if (maxs > best_size) {
                    best_size = maxs;
                    best_m = m;
                    best_n = n;
                }
            }
        }
        boards_of_size[best_size] += 1;
        remaining_cells -= best_size * best_size;
        mark_used(best_m, best_n, best_size);
    }
    cout << count_if(boards_of_size.begin(), boards_of_size.end(),
                     [](int n) { return n > 0; }) 
         << endl;
    for (int size = max(M, N); size > 0; --size) {
        if (boards_of_size[size] > 0)
            cout << size << ' ' << boards_of_size[size] << endl;
    }
}

void read_solve_print_case() {
    Inst inst;
    inst.read();
    inst.solve_print();
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": "; 
        read_solve_print_case();
    }
    return 0;
}
