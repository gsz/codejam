#include <everything.h>

using namespace std;

struct Graph {
    struct Edge {
        bool crossing;
        int destination;
        int T, open_time, closed_time;

        Edge(bool _crossing, int d, int _T = 0, int ot = 0, int ct = 0) :
            crossing(_crossing), destination(d), T(_T), open_time(ot), 
            closed_time(ct) { }
        int cross_time(int start_time);
    };

    int N, M;
    vector<vector<Edge>> V;

    void read();
    int fastest_route(int src, int dst);
};

int Graph::Edge::cross_time(int start_time) {
    if (!crossing)
        return start_time + 2;
    int period = open_time + closed_time;
    int t = ((start_time - T) % period + period) % period;
    if (t < open_time) {
        return start_time + 1;
    } else {
        return start_time + period - t + 1;
    }
}

void Graph::read() {
    cin >> N >> M;
    V.resize(N*M*4);
    for (int n = 0; n < N; ++n) {
        for (int m = 0; m < M; ++m) {
            int S, W, T;
            cin >> S >> W >> T;
            int b = (n * M + m) * 4;
            if (m > 0) {
                int bl = b - 4;
                V[b+0].emplace_back(false, bl+1);
                V[b+2].emplace_back(false, bl+3); 
            }
            if (m < M-1) {
                int br = b + 4;
                V[b+1].emplace_back(false, br+0);
                V[b+3].emplace_back(false, br+2);
            }
            if (n > 0) {
                int bu = b - M*4;
                V[b+0].emplace_back(false, bu+2);
                V[b+1].emplace_back(false, bu+3);
            }
            if (n < N-1) {
                int bd = b + M*4;
                V[b+2].emplace_back(false, bd+0);
                V[b+3].emplace_back(false, bd+1);
            }
            if (S != 0) {
                V[b+0].emplace_back(true, b+2, T, S, W);
                V[b+2].emplace_back(true, b+0, T, S, W);
                V[b+1].emplace_back(true, b+3, T, S, W);
                V[b+3].emplace_back(true, b+1, T, S, W);
            }
            if (W != 0) {
                V[b+0].emplace_back(true, b+1, T+S, W, S);
                V[b+1].emplace_back(true, b+0, T+S, W, S);
                V[b+2].emplace_back(true, b+3, T+S, W, S);
                V[b+3].emplace_back(true, b+2, T+S, W, S);
            }
        }
    }
}

int Graph::fastest_route(int src, int dst) {
    vector<bool> done(V.size(), false);
    vector<int> earliest(V.size(), INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, 
                   greater<pair<int,int>>> q;
    q.emplace(0, src);
    earliest[src] = 0;
    while (!q.empty()) {
        int t, v;
        tie(t, v) = q.top();
        q.pop();
        if (done[v])
            continue;
        done[v] = true;
        earliest[v] = t;
        for (auto &e : V[v]) {
            int t2 = e.cross_time(t);
            if (done[e.destination] || earliest[e.destination] <= t2)
                continue;
            earliest[e.destination] = t2;
            q.emplace(t2, e.destination);
        }
    }
    return earliest[dst];
}

int read_solve_case() {
    Graph G;
    G.read();
    int src = (G.N - 1) * G.M * 4 + 2;
    int dst = (G.M - 1) * 4 + 1;
    return G.fastest_route(src, dst);
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
