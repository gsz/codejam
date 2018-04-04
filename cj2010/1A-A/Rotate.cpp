#include <everything.h>

using namespace std;

int longest_segment(vector<string> &board, char color, int i, int j, 
                    int istep, int jstep) {
    int N = board.size();
    int current = 0, longest = 0;
    while (0 <= i && i < N && 0 <= j && j < N) {
        if (board[i][j] == color) {
            current += 1;
            longest = max(current, longest);
        } else {
            current = 0;
        }
        i += istep;
        j += jstep;
    }
    return longest;
}

bool wincheck(vector<string> &board, char color, int K) {
    int N = board.size();
    for (int i = 0; i < N; ++i) {
        if (longest_segment(board, color, i, 0, 0, 1) >= K
                || longest_segment(board, color, 0, i, 1, 0) >= K
                || longest_segment(board, color, i, 0, 1, 1) >= K
                || longest_segment(board, color, 0, i, 1, 1) >= K
                || longest_segment(board, color, i, 0, -1, 1) >= K
                || longest_segment(board, color, N-1, i, -1, 1) >= K) {
            return true;
        }
    }
    return false;
}

string read_solve_case() {
    int N, K;
    cin >> N >> K;
    vector<string> board(N);
    for (int i = 0; i < N; ++i)
        cin >> board[i];
    for (int i = 0; i < N; ++i) {
        int j2 = N-1;
        for (int j = N-1; j >= 0; --j) {
            if (board[i][j] != '.')
                board[i][j2--] = board[i][j];  
        }
        for (int j = j2; j >= 0; --j)
            board[i][j] = '.';
    }
    vector<string> board2(N, string(N, '.'));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            board2[i][j] = board[N-1 - j][i];
    bool red = wincheck(board2, 'R', K);
    bool blue = wincheck(board2, 'B', K);
    if (red && blue) {
        return "Both";
    } else if (red) {
        return "Red";
    } else if (blue) {
        return "Blue";
    } else {
        return "Neither";
    }
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

