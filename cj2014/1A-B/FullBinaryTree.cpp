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

pair<int,int> cost_size_aux(const vector<vector<int>>& neighbors, int root,
                            int parent) {
    vector<int> children(neighbors[root].size());
    children.erase(remove_copy(neighbors[root].begin(), neighbors[root].end(), 
                               children.begin(), parent),
                   children.end());
    if (children.empty()) {
        return make_pair(0, 1);
    } else if (children.size() == 1) {
        int subsize = cost_size_aux(neighbors, children[0], root).second;
        return make_pair(subsize, subsize+1);
    } else {
        int size = 0;
        vector<int> sizecost_diffs;
        for (int n : children) {
            pair<int,int> subcost_size = cost_size_aux(neighbors, n, root);
            size += subcost_size.second;
            sizecost_diffs.push_back(subcost_size.second - subcost_size.first);
        }
        auto idiff_max = max_element(sizecost_diffs.begin(), 
                                     sizecost_diffs.end());
        int diff_max = *idiff_max;
        swap(*idiff_max, *(sizecost_diffs.end()-1));
        sizecost_diffs.pop_back();
        int diff_almost_max = *max_element(sizecost_diffs.begin(), 
                                           sizecost_diffs.end());
        return make_pair(size - diff_max - diff_almost_max, size+1);
    }
}

pair<int, int> cost_size(const vector<vector<int>>& neighbors, int root) {
    return cost_size_aux(neighbors, root, -1);
}

int read_solve_case() {
    int N;
    cin >> N;
    vector<vector<int>> neighbors(N);
    for (int i = 0; i < N-1; ++i) {
        int X, Y;
        cin >> X >> Y;
        neighbors[X-1].push_back(Y-1);
        neighbors[Y-1].push_back(X-1);
    }
    int min_cost = N+1;
    for (int i = 0; i < N; ++i) {
        min_cost = min(min_cost, cost_size(neighbors, i).first); }
    return min_cost;
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

