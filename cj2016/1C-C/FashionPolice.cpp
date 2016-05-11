#include <cassert>
#include <limits>
#include <memory>
#include <ios>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

void read_solve_case() {
    int J, P, S, K;
    cin >> J >> P >> S >> K;
    if (K >= S) {
        cout << J * P * S << endl;
        for (int j = 1; j <= J; ++j) {
            for (int p = 1; p <= P; ++p) {
                for (int s = 1; s <= S; ++s) {
                    cout << j << ' ' << p << ' ' << s << endl; }
            }
        }
        return;
    }
    cout << J * P * K << endl;
    for (int j = 1; j <= J; ++j) {
        int k = 0;
        for (int p = 1; p <= P; ++p) {
            for (int l = 0; l < K; ++l) {
                cout << j << ' ' << p << ' ' << (j + k++) % S + 1 << endl; }
        }
    }
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": ";
        read_solve_case();
    }
    return 0;
}

