#include <everything.h>

using namespace std;

int read_solve_case() {
    int N, S, p;
    cin >> N >> S >> p;
    int reachable_unsurprisingly = 0;
    int reachable_only_surprisingly = 0;
    for (int n = 0; n < N; ++n) {
        int t;
        cin >> t;
        int max_surprising, max_unsurprising;
        if (t % 3 == 0) {
            max_unsurprising = t / 3;
            max_surprising = max_unsurprising + (t > 0 ? 1 : 0);
        } else if (t % 3 == 1) {
            max_unsurprising = max_surprising = t / 3 + 1;
        } else {
            max_unsurprising = t / 3 + 1;
            max_surprising = max_unsurprising + 1;
        }
        if (max_unsurprising >= p) {
            reachable_unsurprisingly += 1;
        } else if (max_surprising >= p) {
            reachable_only_surprisingly += 1;
        }
    }
    return reachable_unsurprisingly + min(reachable_only_surprisingly, S);
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

