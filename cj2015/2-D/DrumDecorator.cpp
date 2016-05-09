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

const u64 MODULUS = 1'000'000'007;

class ChoicesCache {
    vector<vector<u64>> vals;
public:
    ChoicesCache(int maxn);
    u64 operator()(int n, int k) const { return vals[n][k]; }
};

ChoicesCache::ChoicesCache(int maxn) {
    for (int n = 0; n < maxn; ++n) {
        vals.emplace_back(maxn, 0);
        for (int k = 0; k <= n; ++k) {
            u64 result = 1;
            for (int i = 0; n - i > n - k; ++i) {
                result = result * (n - i) / (i+1); }
            vals[n][k] = result % MODULUS;
        }
    }
}

class PowCache {
    vector<u64> vals;
public:
    PowCache(u64 base, int maxn): vals(max(1, maxn)) {
        vals[0] = 1;
        for (int i = 1; i < maxn; ++i) {
            vals[i] = vals[i-1] * base % MODULUS; }
    }
    u64 operator()(int i) const { return vals[i]; }
};

ChoicesCache num_choices(40);
PowCache pow3(3, 100);
PowCache pow4(4, 100);
PowCache pow6(6, 100);

u64 num_arrangements(int i, int j, int k, int l) {
    u64 result = num_choices(i+j+k+l, i);
    result = result * num_choices(j+k+l, j) % MODULUS;
    result = result * num_choices(k+l, k) % MODULUS;
    return result;
}

u64 read_solve_case() {
    int R, C;
    cin >> R >> C;
    u64 num_decorations = 0;
    for (int i = 0; i*3 - 2 <= R; ++i) {
        for (int j = 0; j*4 <= (R - i*3 + 2) * (C % 3 == 0); ++j) {
            for (int k = 0; k*4 <= (R - i*3 - j*4 + 2) * (C % 6 == 0); ++k) {
                int space = R - i - j*2 - k*2; // fillers
                space -= (i + j + k - 1) * 2; // spacers
                if (C % 4 != 0 && space > 4) {
                    continue; }
                if (space % 5 == 0 || space % 5 == 2 || space % 5 == 4) {
                    int l = space / 5;
                    u64 increase = num_arrangements(i, j, k, l);
                    increase = increase * pow3(max(j-1, 0)) % MODULUS;
                    increase = increase * pow6(max(k-1, 0)) % MODULUS;
                    increase = increase * pow4(max(l-1, 0)) % MODULUS;
                    if (j > 0 && k > 0) {
                        increase *= 3; }
                    if (k > 0 && l > 0) {
                        increase *= 2; }
                    if (space % 5 == 2) {
                        increase *= 2; }
                    num_decorations = (num_decorations + increase) % MODULUS;
                }
            }
        }
    }
    return num_decorations;
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

