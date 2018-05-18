#include <everything.h>

using namespace std;

struct Combinations {
    vector<vector<double>> vals;

    Combinations(int maxn);
    double operator()(int n, int k) { return vals[n][k]; }
};

Combinations::Combinations(int maxn) :
        vals(maxn+1, vector<double>(maxn+1, 0))
{
    vals[0][0] = 1;
    for (int n = 1; n <= maxn; ++n) {
        vals[n][0] = 1;
        for (int k = 1; k <= n; ++k)
            vals[n][k] = vals[n-1][k-1] + vals[n-1][k];
    }
}

Combinations combs(40);

double read_solve_case() {
    int C, N; 
    cin >> C >> N;
    vector<double> ev_remaining(C+1);
    ev_remaining[0] = 0;
    for (int m = 1; m <= C - N; ++m) {
        double ppb_some_new = 1 - combs(C - m, N) / combs(C, N);
        double ev = 1;
        for (int numnew = 1; numnew <= min(N, m); ++numnew) {
            double ppb_n_new = (combs(m, numnew) * combs(C-m, N-numnew)
                                / combs(C, N));
            ev += ppb_n_new * ev_remaining[m - numnew];
        }
        ev_remaining[m] = ev / ppb_some_new;
    }
    return 1 + ev_remaining[C - N];
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    cout << setprecision(6) << fixed;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl;
    }
    return 0;
}
