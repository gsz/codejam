#include <everything.h>

using namespace std;

string read_solve_case() {
    string S;
    u32 K;
    cin >> S >> K;
    u32 flips = 0;
    u32 i = 0;
    do {
        if (S[i] == '+')
            continue;
        if (i + K > S.size())
            return "IMPOSSIBLE";
        flips += 1;
        for (u32 j = i; j < i + K; ++j)
            S[j] = S[j] == '+' ? '-' : '+';
    } while (++i < S.size());
    return to_string(flips);
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
