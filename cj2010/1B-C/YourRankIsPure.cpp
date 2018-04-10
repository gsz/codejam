#include <everything.h>

using namespace std;

const int MOD = 100003;
const int MAXN = 500;

struct Combinations {
    vector<vector<u64>> vals;

    Combinations(int maxn);
    u64 operator()(int n, int k) const { return vals[n][k]; }
};

Combinations::Combinations(int maxn) 
: vals(maxn+1, vector<u64>(maxn+1, 0)) {
    for (int n = 0; n <= maxn; ++n)
        vals[n][0] = 1;
    for (int n = 1; n <= maxn; ++n)
        for (int k = 1; k <= n; ++k)
            vals[n][k] = (vals[n-1][k] + vals[n-1][k-1]) % MOD;
}

const Combinations combs(MAXN);

struct Precalc {
    vector<u64> vals;

    Precalc(int maxn);
};

Precalc::Precalc(int maxn)
: vals(maxn+1) {
    // sol[k][l] -- number of subsets {2..k} where k is pure and has
    //              rank at least l (modulo the thing)
    vector<vector<u64>> sol(maxn+1, vector<u64>(maxn, 0));
    for (int k = 2; k <= maxn; ++k) {
        sol[k][1] = 1;
        vals[k] = 1;
        for (int l = 2; l < k; ++l) {
            sol[k][l] = 0;
            int min_l_rank = max(l - (k - l), 1);
            for (int m = min_l_rank; m < l; ++m) {
                sol[k][l] += (sol[l][m] * combs(k - l - 1, l - m - 1));
                sol[k][l] %= MOD;
            }
            vals[k] = (vals[k] + sol[k][l]) % MOD;
        }
    }
}

const Precalc precalc(MAXN);

u64 read_solve_case() {
    int n;
    cin >> n;
    return precalc.vals[n];
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
