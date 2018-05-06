#include <iostream>
#include <vector>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

string read_solve_case() {
    int R, C, H, V;
    cin >> R >> C >> H >> V;
    vector<vector<bool>> chips(R, vector<bool>(C, false));
    for (int i = 0; i < R; ++i) {
        string row;
        cin >> row;
        for (int j = 0; j < C; ++j) {
            if (row[j] == '@') {
                chips[i][j] = true;
            }
        }
    }
    for (int i = 1; i < R; ++i) {
        for (int j = 1; j < C; ++j) {
            int ul = 0, ur = 0, ll = 0, lr = 0;
            for (int i2 = 0; i2 < i; ++i2) {
                for (int j2 = 0; j2 < j; ++j2)
                    ul += chips[i2][j2];
                for (int j2 = j; j2 < C; ++j2)
                    ur += chips[i2][j2];
            }
            for (int i2 = i; i2 < R; ++i2) {
                for (int j2 = 0; j2 < j; ++j2)
                    ll += chips[i2][j2];
                for (int j2 = j; j2 < C; ++j2)
                    lr += chips[i2][j2];
            }
            if (ul == ur && ur == ll && ll == lr)
                return "POSSIBLE";
        }
    }
    return "IMPOSSIBLE";
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
