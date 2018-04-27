#include <everything.h>

using namespace std;

int max_tests(i64 L, i64 P, i64 C) {
    if (L * C >= P)
        return 0;
    double logL = log(L);
    double logP = log(P);
    double logmid = (logL + logP) / 2;
    double loghi = log(ceil(exp(logmid)));
    double loglo = log(floor(exp(logmid)));
    if (logmid - loglo < loghi - logmid) {
        int testnum = static_cast<int>(floor(exp(logmid)));
        return 1 + max_tests(testnum, P, C);
    } else {
        int testnum = static_cast<int>(ceil(exp(logmid)));
        return 1 + max_tests(L, testnum, C);
    }
}

int read_solve_case() {
    i64 L, P, C;
    cin >> L >> P >> C;
    return max_tests(L, P, C);
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
