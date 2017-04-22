#include <everything.h>

using namespace std;

double read_solve_case() {
    int N;
    double D;
    cin >> D >> N;
    double worst_time = 0;
    for (int i = 0; i < N; ++i) {
        double K, S;
        cin >> K >> S;
        worst_time = max(worst_time, (D - K) / S);
    }
    return D / worst_time;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    cout << setprecision(9);
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl;
    }
    return 0;
}

