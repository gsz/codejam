#include <everything.h>

using namespace std;

int read_solve_case() {
    int N, X;
    cin >> N >> X;
    vector<int> S(N);
    for (int i = 0; i < N; ++i) {
        cin >> S[i]; }
    sort(S.begin(), S.end());
    int ibig = N - 1, ismall = 0;
    int num_disks = 0;
    while (ibig >= ismall) {
        num_disks += 1;
        if (S[ibig] + S[ismall] <= X) {
            ismall += 1; }
        ibig -= 1;
    }
    return num_disks;
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

