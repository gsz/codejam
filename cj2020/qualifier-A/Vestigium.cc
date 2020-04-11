#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

using namespace std;

string read_solve_case() {
    u32 N, badrows{0}, trace{0};
    cin >> N;
    unordered_set<u32> rowset;
    vector<bool> badcols(N, false);
    vector<unordered_set<u32>> colsets(N);
    for (u32 i = 0; i < N; ++i) {
        rowset.clear();
        bool badrow{false};
        for (u32 j = 0; j < N; ++j) {
            u32 Mij;
            cin >> Mij;
            if (i == j)
                trace += Mij;
            if (rowset.count(Mij))
                badrow = true;
            rowset.insert(Mij);
            if (colsets[j].count(Mij))
                badcols[j] = true;
            colsets[j].insert(Mij);
        }
        badrows += badrow;
    }
    return (to_string(trace) + ' ' + to_string(badrows) + ' ' +
            to_string(count(badcols.begin(), badcols.end(), true)));
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
