#include <everything.h>

using namespace std;

u64 read_solve_case() {
    u32 R, k, N;
    cin >> R >> k >> N;
    vector<u32> g(N);
    for (u32 i = 0; i < N; ++i)
        cin >> g[i];
    vector<u32> precalc_next(N);
    vector<u64> precalc_earnings(N);
    for (u32 i = 0; i < N; ++i) {
        u32 space_remaining = k - g[i];
        u32 earnings = g[i];
        u32 j;
        for (j = (i + 1) % N; j != i; j = (j + 1) % N) {
            if (space_remaining < g[j])
                break;
            space_remaining -= g[j];
            earnings += g[j];
        }
        precalc_next[i] = j;
        precalc_earnings[i] = earnings;
    }
    u64 total_earnings = 0;
    u32 queue_idx = 0;
    while (R--) {
        total_earnings += precalc_earnings[queue_idx];
        queue_idx = precalc_next[queue_idx];
    }
    return total_earnings;
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
