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
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

struct BipartiteGraph {
    vector<unordered_set<u32>> G;
    unordered_set<u32> L;
};

struct BipartiteMatchingData {
    const BipartiteGraph &graph;
    BipartiteGraph residual;
    unordered_set<int> L_matched, R_matched;
    BipartiteMatchingData(const BipartiteGraph& graph): graph(graph), 
        residual(graph), L_matched(), R_matched() { };
};

vector<u32> residual_bfs(BipartiteMatchingData& d) {
    unordered_map<u32, u32> preds;
    unordered_set<u32> visited;
    vector<u32> fringe1, fringe2;
    for (u32 vl : d.graph.L) {
        if (!d.L_matched.count(vl)) {
            fringe1.push_back(vl);
            visited.insert(vl);
        }
    }
    int path_len = 0;
    while (!fringe1.empty()) {
        fringe2.clear();
        for (u32 v1 : fringe1) {
            if (!d.graph.L.count(v1) && !d.R_matched.count(v1)) {
                vector<u32> result(path_len+1);
                result.back() = v1;
                while (--path_len >= 0) {
                    result[path_len] = preds[result[path_len+1]]; }
                return result;
            }
            for (u32 v2 : d.residual.G[v1]) {
                if (!visited.count(v2)) {
                    fringe2.push_back(v2);
                    preds[v2] = v1;
                    visited.insert(v2);
                }
            }
        }
        path_len += 1;
        swap(fringe1, fringe2);
    }
    return vector<u32>(); 
}

void augment(BipartiteMatchingData& d, vector<u32> path) {
    d.L_matched.insert(path.front());
    d.R_matched.insert(path.back());
    for (u32 i = 0; i + 1 < path.size(); ++i) {
        d.residual.G[path[i]].erase(path[i+1]);
        d.residual.G[path[i+1]].insert(path[i]);
    }
}

int min_edge_cover_size(const BipartiteGraph& graph) {
    BipartiteMatchingData d(graph);
    vector<u32> augmenting_path;
    while (!(augmenting_path = residual_bfs(d)).empty()) {
        augment(d, augmenting_path); }
    int cover_size = d.L_matched.size();
    for (u32 v = 0; v < graph.G.size(); ++v) {
        if (!d.L_matched.count(v) && !d.R_matched.count(v)) {
            cover_size += 1; }
    }
    return cover_size;
}

int read_solve_case() {
    int N;
    cin >> N;
    unordered_map<string, u32> L_words, R_words;
    u32 num_vertices = 0;
    BipartiteGraph graph;
    graph.G.resize(2*N);
    for (int i = 0; i < N; ++i) {
        string wl, wr;
        cin >> wl >> wr;
        if (!L_words.count(wl)) {
            L_words[wl] = num_vertices++; }
            graph.L.insert(L_words[wl]);
        if (!R_words.count(wr)) {
            R_words[wr] = num_vertices++; }
        graph.G[L_words[wl]].insert(R_words[wr]);
    }
    graph.G.resize(num_vertices);
    return N - min_edge_cover_size(graph);
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
