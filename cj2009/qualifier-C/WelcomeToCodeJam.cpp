#include <everything.h>

using namespace std;

const int MOD = 10000;
const string pat = "welcome to code jam";

int read_solve_case() {
    string line;
    getline(cin >> std::ws, line);
    int N = line.size(), M = pat.size();
    vector<vector<int>> counts(M+1, vector<int>(N+1, 0));
    fill(counts[M].begin(), counts[M].end(), 1);
    for (int j = M-1; j >= 0; --j) {
        for (int i = N-1; i >= 0; --i) {
            int count = counts[j][i+1];
            if (line[i] == pat[j])
                count += counts[j+1][i+1];
            counts[j][i] = count % MOD;
        }
    }
    return counts[0][0];
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << setw(4) << setfill('0') <<
            read_solve_case() << endl;
    }
    return 0;
}
