#include <cassert>
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

int read_solve_case() {
    u64 C, D, V;
    vector<u64> denoms;
    cin >> C >> D >> V;
    for (u32 i = 0; i < D; ++i) {
        u64 denom;
        cin >> denom;
        denoms.push_back(denom);
    }
    u32 extra_needed = 0;
    u64 current_max = 0;
    u32 idenom = 0;
    while (current_max < V) {
        if (idenom < denoms.size() && denoms[idenom] <= current_max + 1) {
            current_max += denoms[idenom] * C;
            ++idenom;
        } else {
            current_max += (current_max + 1) * C;
            ++extra_needed;
        }
    }
    return extra_needed;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    u32 T;
    cin >> T;
    for (u32 ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl;
    }
    return 0;
}

