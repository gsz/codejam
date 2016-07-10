#include <everything.h>

using namespace std;

int extrude_wall(int N, int M, int dwall, int diag[4], int straight[4], 
                 int n, int m, 
                 int *newdiag, int *newstraight, int *newn, int *newm) {
    int diagonal_wall[4], straight_wall[4];
    copy(diag, diag+4, diagonal_wall);
    copy(straight, straight+4, straight_wall);
    int increase = 0;
    if (diagonal_wall[dwall] >= 0) {
        increase += 1 + diagonal_wall[dwall];
        diagonal_wall[dwall] -= 1;
        for (int i : {-1, 0}) {
            int swall = (dwall + i + 4) % 4;
            straight_wall[swall] += 1;
            if (straight_wall[swall] >= 3 && 
                    (swall % 2 == 0 ? n < N : m < M)) {
                (swall % 2 == 0 ? n : m) += 1;
                straight_wall[swall] -= 2;
                diagonal_wall[swall] += 1;
                diagonal_wall[(swall + 1) % 4] += 1;
                increase += 1;
            }
        }
    }
    if (newdiag && newstraight && newn && newm) {
        copy(diagonal_wall, diagonal_wall+4, newdiag);
        copy(straight_wall, straight_wall+4, newstraight);
        *newn = n;
        *newm = m;
    }
    return increase;
}

int read_solve_case() {
    int N, M, K;
    cin >> N >> M >> K;
    int n, m, k;
    tie(N, M) = minmax({N, M});
    if (K < 5 || N < 3) {
        return K; } 
    n = m = 3;
    k = 5;
    int stones = 4;
    int diagonal_wall[4] = {0, 0, 0, 0};
    int straight_wall[4] = {1, 1, 1, 1};
    while (k < K) {
        int bestdiag = 0;
        int bestgrowth = -1;
        for (int i = 0; i < 4; ++i) {
                int growth = extrude_wall(N, M, i, diagonal_wall, 
                                          straight_wall, n, m, 
                                          NULL, NULL, NULL, NULL);
                if (growth > bestgrowth) {
                    bestgrowth = growth;
                    bestdiag = i;
                }
        }
        k += extrude_wall(N, M, bestdiag, diagonal_wall, straight_wall, n, m,
                          diagonal_wall, straight_wall, &n, &m);
        stones += 1;
    }
    return stones;
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

