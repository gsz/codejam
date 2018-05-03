#include <everything.h>

using namespace std;

string read_solve_case() {
    int N, K;
    cin >> N >> K;
    if (K % (1 << N) == ((1 << N) - 1)) {
        return "ON";
    } else {
        return "OFF";
    }
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
