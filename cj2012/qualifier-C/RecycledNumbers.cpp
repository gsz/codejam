#include <everything.h>

using namespace std;

const int powers_of_10[8] = {1, 10, 100, 1000, 10'000, 100'000, 1'000'000,
                             10'000'000};

int read_solve_case() {
    int A, B;
    cin >> A >> B;
    int recycled_pairs = 0;
    for (int n = A; n <= B; ++n) {
        int log10n;
        for (log10n = 0; powers_of_10[log10n + 1] <= n; ++log10n) { }
        for (int p = 1; p <= log10n; ++p) {
            if (n % powers_of_10[p] < powers_of_10[p-1]) {
                continue; }
            int recycled = (n / powers_of_10[p] +
                            n % powers_of_10[p] * powers_of_10[log10n-p+1]);
            if (recycled == n) {
                break; }
            if (recycled > n && recycled <= B) {
                recycled_pairs += 1; }
        }
    }
    return recycled_pairs;
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

