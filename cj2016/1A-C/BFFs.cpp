#include <cassert>
#include <memory>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

class graph {
public:
    struct vertex {
        int succ;
        int dest_sink;
        int dest_in_sink;
        int pathnum;
        int distance;
        int visit_iteration;
        vertex(): dest_sink(-1), visit_iteration(-1) { }
    };

    class sinkpair {
        sinkpair(graph &, int, int);
    public:
        friend class graph;
        vector<int> sources;
    };
private:
    vector<vertex> vertices;
    vector<sinkpair> sinks;
public:
    graph(int N): vertices(N) { };
    void connect(int from, int to) { vertices[from].succ = to; };
    int make_sink(int v1, int v2);
    void attach_to_sink(int sink, int newv, int attachment_point);
    vertex& operator[](size_t idx) { return vertices[idx]; };
    size_t numsinks() const { return sinks.size(); };
    sinkpair& getsink(size_t idx) { return sinks[idx]; };
    int numverts() const { return vertices.size(); };
};

graph::sinkpair::sinkpair(graph &g, int v1, int v2) {
    vertex &rv1 = g[v1];
    vertex &rv2 = g[v2];
    rv1.dest_in_sink = 0;
    rv2.dest_in_sink = 1;
    rv1.distance = rv2.distance = 0;
    sources.push_back(v1);
    rv1.pathnum = 0;
    sources.push_back(v2);
    rv2.pathnum = 1;
}

int graph::make_sink(int v1, int v2) {
    int result = sinks.size();
    sinks.push_back(sinkpair(*this, v1, v2));
    vertices[v1].dest_sink = vertices[v2].dest_sink = result;
    return result;
}

void graph::attach_to_sink(int sink, int newv, int attachment_point) {
    vertex &rnewv = vertices[newv];
    vertex &ratt = vertices[attachment_point];
    assert(ratt.dest_sink == sink);
    rnewv.dest_sink = ratt.dest_sink;
    rnewv.dest_in_sink = ratt.dest_in_sink;
    rnewv.distance = ratt.distance + 1;
    if (sinks[sink].sources[ratt.pathnum] == attachment_point) {
        rnewv.pathnum = ratt.pathnum;
        sinks[sink].sources[rnewv.pathnum] = newv;
    } else {
        rnewv.pathnum = sinks[sink].sources.size();
        sinks[sink].sources.push_back(newv);
    }
}

int analyze_graph(graph &G) {
    int max_proper_cycle = 0;
    vector<int> path;
    for (int v = 0; v < G.numverts(); ++v) {
        int u = v;
        path.clear();
        while (G[u].visit_iteration == -1) {
            path.push_back(u);
            G[u].visit_iteration = v;
            u = G[u].succ;
        }
        if (G[u].visit_iteration != v) {
            if (G[u].dest_sink == -1 || path.size() == 0) 
                continue;
            for (auto iv = path.rbegin(); iv != path.rend(); ++iv) {
                G.attach_to_sink(G[u].dest_sink, *iv, u);
                u = *iv;
            }
        } else {
            auto icycle_start = find(path.rbegin(), path.rend(), u);
            if (icycle_start - path.rbegin() > 1) {
                max_proper_cycle = max(max_proper_cycle, 
                                       int(icycle_start - path.rbegin() + 1));
                continue;
            } 
            int z = path.back();
            path.pop_back();
            int w = path.back();
            path.pop_back();
            int dest_sink = G.make_sink(w, z);
            for (auto ivp = path.rbegin(); ivp != path.rend(); ++ivp) {
                G.attach_to_sink(dest_sink, *ivp, w);
                w = *ivp;
            }
        }
    }
    return max_proper_cycle;
}

int read_solve_case() {
    int N;
    cin >> N;
    graph G(N);
    for (int n = 0; n < N; ++n) {
        int bffidx;
        cin >> bffidx;
        G.connect(n, bffidx-1);
    }
    int max_proper_cycle = analyze_graph(G);
    int max_fanboy_circle = 0;
    for (size_t si = 0; si < G.numsinks(); ++si) {
        int max0 = 0, max1 = 0;
        for (auto vi : G.getsink(si).sources) {
            if (G[vi].dest_in_sink == 0) {
                max0 = max(max0, G[vi].distance);
            } else {
                max1 = max(max1, G[vi].distance);
            }
        }
        max_fanboy_circle += 2 + max0 + max1;
    }
    return max(max_fanboy_circle, max_proper_cycle);
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
