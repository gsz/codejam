#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

double read_solve_case() {
    int N;
    double P, W, H;
    cin >> N >> P;
    for (int i = 0; i < N; ++i)
        cin >> W >> H;
    double perim = N * 2 * (W + H);
    double minbonus = 2 * min(W, H);
    double maxbonus = 2 * sqrt(W*W + H*H);
    int maxcuts = min(N, static_cast<int>(floor((P - perim) / minbonus)));
    return min(P, perim + maxcuts * maxbonus);
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    cout << setprecision(8) << fixed;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl;
    }
    return 0;
}
