#include <climits>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

void solve_case_interactive() {
    int N;
    cin >> N;
    if (N == -1)
        exit(1);
    vector<int> occurences(N, 0);
    unordered_set<int> remaining_flavors;
    for (int i = 0; i < N; ++i)
        remaining_flavors.insert(i);  
    for (int i = 0; i < N; ++i) {
        int D;
        cin >> D;
        unordered_set<int> liked_flavors;
        for (int j = 0; j < D; ++j) {
            int f;
            cin >> f;
            liked_flavors.insert(f);
            occurences[f] += 1;
        }
        int best_flavor = -1, best_occurs = INT_MAX;
        for (int f : liked_flavors) {
            if (remaining_flavors.count(f) && occurences[f] < best_occurs) {
                best_flavor = f;
                best_occurs = occurences[f];
            }
        }
        cout << best_flavor << endl;
        remaining_flavors.erase(best_flavor);
    }
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        solve_case_interactive();
    }
    return 0;
}
