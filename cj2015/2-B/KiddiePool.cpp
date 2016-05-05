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

double epsilon = 1e-10;

struct src {
    double R, C;
    src(double nR, double nC): R(nR), C(nC) { }
    bool operator<(src& other) { return C < other.C; }
};

double read_solve_case() {
    int N;
    double V, X;
    cin >> N >> V >> X;
    vector<src> sources;
    double energy = 0.0, flow = 0.0;
    for (int i = 0; i < N; ++i) {
        double R, C;
        cin >> R >> C;
        sources.emplace_back(R, C);
        flow += R;
        energy += R * C;
    }
    if (abs(energy / flow - X) <= epsilon) {
        return V / flow; } 
    double diffsgn = energy / flow - X;
    sort(sources.begin(), sources.end());
    if (sources[0].C > X || sources.back().C < X) {
        return numeric_limits<double>::infinity(); }
    if (energy / flow < X) {
        reverse(sources.begin(), sources.end()); }
    while (!sources.empty()) {
        src s = sources.back();
        sources.pop_back();
        energy = flow = 0.0;
        for (src& s1 : sources) {
            energy += s1.R * s1.C;
            flow += s1.R;
        }
        if (s.C == X) {
            flow += s.R;
            break;
        } else if ((energy / flow - X) * diffsgn < 0) {
            flow += (X * flow - energy) / (s.C - X);
            break;
        }
    }
    return V / flow;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    cout << fixed << setprecision(9);
    for (int ci = 1; ci <= T; ++ci) {
        double result = read_solve_case();
        cout << "Case #" << ci << ": ";
        if (isinf(result)) {
            cout << "IMPOSSIBLE";
        } else {
            cout << result;
        }
        cout << endl;
    }
    return 0;
}
