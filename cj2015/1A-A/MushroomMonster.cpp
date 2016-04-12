#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

string read_solve_case() {
    int N;
    vector<int> ms;
    cin >> N;
    int eaten1 = 0;
    int eating_rate = 0;
    int m = 0, prev_m;
    for (int i = 0; i < N; ++i) {
        prev_m = m;
        cin >> m;
        if (m < prev_m) {
            eaten1 += prev_m - m;
            eating_rate = max(eating_rate, prev_m - m);
        }
        ms.push_back(m);
    }
    int eaten2 = 0;
    ms.pop_back();
    for (int m : ms) {
        eaten2 += min(eating_rate, m);
    }
    stringstream result;
    result << eaten1 << ' ' << eaten2;
    return result.str();
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

