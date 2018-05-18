#include <everything.h>

using namespace std;

string read_solve_case() {
    string N;
    cin >> N;
    if (!next_permutation(N.begin(), N.end())) {
        auto di = find_if(N.begin(), N.end(),
                          [](char d) { return d != '0'; });
        swap(N[0], *di);
        N.insert(1, 1, '0');
    }
    return N;
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
