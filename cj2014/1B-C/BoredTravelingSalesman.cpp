#include <cassert>
#include <limits>
#include <memory>
#include <ios>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <list>
#include <queue>
#include <random>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

struct vertex {
    bool visited;
    u32 zipcode;
    vector<int> neighbors;
};

struct dfs_record {
    u32 v_idx;
    list<u32> succs;
};

class CaseSolver {
    vector<vertex> graph;
    vector<dfs_record> dfs_stack;
    void dfs_push(u32 vidx);
    void dfs_pop(u32 levels=1) { for (u32 i = 0; i < levels; ++i) { 
        dfs_stack.pop_back(); } };
    void dfs_descend() { 
        dfs_push(dfs_stack.back().succs.front()); };
    void next_viable_successor(dfs_record& r);
    size_t num_reachable(vector<u32> from);
public:
    void read_case();
    string solve();
};

void CaseSolver::dfs_push(u32 vidx) {
    dfs_record newr;
    newr.v_idx = vidx;
    newr.succs.resize(graph[vidx].neighbors.size());
    copy(graph[vidx].neighbors.begin(), graph[vidx].neighbors.end(),
         newr.succs.begin());
    dfs_stack.push_back(move(newr));
}
    
void CaseSolver::next_viable_successor(dfs_record& r) {
    while (!r.succs.empty() && graph[r.succs.front()].visited) {
        r.succs.pop_front(); }
}

size_t CaseSolver::num_reachable(vector<u32> from) {
    unordered_set<u32> bfs_visited;
    vector<u32> next;
    while (!from.empty()) {
        next.clear();
        for (u32 vi : from) {
            for (u32 vi2 : graph[vi].neighbors) {
                if (!bfs_visited.count(vi2) && !graph[vi2].visited) {
                    next.push_back(vi2); }
            }
        }
        bfs_visited.insert(next.begin(), next.end());
        swap(from, next);
    }
    return bfs_visited.size();
}

void CaseSolver::read_case() {
    int N, M;
    cin >> N >> M;
    graph.resize(N);
    for (int n = 0; n < N; ++n) {
        cin >> graph[n].zipcode; }
    for (int m = 0; m < M; ++m) {
        int i, j;
        cin >> i >> j;
        graph[i-1].neighbors.push_back(j-1);
        graph[j-1].neighbors.push_back(i-1);
    }
    auto zipcode_less = [&](int iv1, int iv2) { 
        return graph[iv1].zipcode < graph[iv2].zipcode; 
    };
    for (vertex& v : graph) {
        sort(v.neighbors.begin(), v.neighbors.end(), zipcode_less); }
}

string CaseSolver::solve() {
    u32 start_vertex = 0, min_zipcode = 999999;
    for (u32 i = 0; i < graph.size(); ++i) {
        if (graph[i].zipcode < min_zipcode) {
            min_zipcode = graph[i].zipcode;
            start_vertex = i;
        }
    }
    dfs_push(start_vertex);
    int num_visited = 0;
    ostringstream result;
    while (!dfs_stack.empty()) {
        auto& r = dfs_stack.back();
        auto& v = graph[r.v_idx];
        if (!v.visited) {
            num_visited += 1;
            v.visited = true;
            result << v.zipcode;
        }
        next_viable_successor(r);
        if (r.succs.empty()) {
            dfs_pop();
            continue;
        }
        u32 min_zipcode = graph[r.succs.front()].zipcode;
        u32 best_ascent = 0;
        for (u32 ascent = 1; ascent < dfs_stack.size(); ++ascent) {
            vector<u32> ancestors(dfs_stack.size() - ascent);
            transform(dfs_stack.begin(), dfs_stack.end() - ascent,
                      ancestors.begin(), [](auto& r) { return r.v_idx; });
            if (num_reachable(ancestors) + num_visited < graph.size()) {
                break; }
            auto& r_back = *(dfs_stack.end()-ascent-1);
            auto& v_back = graph[r_back.v_idx];
            next_viable_successor(r_back);
            if (r_back.succs.empty()) {
                continue; }
            if (graph[r_back.succs.front()].zipcode < min_zipcode) {
                min_zipcode = graph[r_back.succs.front()].zipcode;
                best_ascent = ascent;
            }
        }
        dfs_pop(best_ascent);
        dfs_descend();
    }
    return result.str();
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": ";
        CaseSolver cs;
        cs.read_case();
        cout << cs.solve() << endl;
    }
    return 0;
}
