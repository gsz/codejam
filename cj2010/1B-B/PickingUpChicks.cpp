#include <everything.h>

using namespace std;

string read_solve_case() {
    int N, K, B, T;
    cin >> N >> K >> B >> T;
    vector<int> X(N), V(N);
    for (int i = 0; i < N; ++i)
        cin >> X[i];
    for (int i = 0; i < N; ++i)
        cin >> V[i];
    int slows = 0, swaps = 0;
    for (int i = N-1; i >= 0 && K > 0; --i) {
        if (B - X[i] > V[i] * T) {
            slows += 1;
        } else {
            K -= 1;
            swaps += slows;
        }
    }
    return (K == 0 ? to_string(swaps) : "IMPOSSIBLE");
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
