#include <everything.h>

using namespace std;

typedef vector<unordered_set<u32>> Graph;

class FordFulkerson {
    const Graph& G;
    u32 V;
    Graph residual;
    u32 flow_size;
    u32 s, t;
    vector<u32> find_path() const;
    void increase_flow(const vector<u32>& path);
public:
    FordFulkerson(const Graph& G, u32 s, u32 t);
    u32 max_flow_size() const { return flow_size; };
};

FordFulkerson::FordFulkerson(const Graph& G, u32 s, u32 t):
    G(G), V(G.size()), residual(G), flow_size(0), s(s), t(t)
{
    assert(s != t);
    vector<u32> augmenting_path;
    while (!(augmenting_path = find_path()).empty()) {
        increase_flow(augmenting_path);
    }
}

vector<u32> FordFulkerson::find_path() const {
    vector<bool> visited(V);
    vector<u32> predecessor(V);
    predecessor[s] = V+1;
    visited[s] = true;
    for (deque<u32> q{s}; !q.empty(); q.pop_front()) {
        auto v = q.front();
        for (auto u : residual[v]) {
            if (visited[u]) {
                continue; }
            visited[u] = true;
            predecessor[u] = v;
            if (u == t) {
                q.resize(1);
                break;
            } else {
                q.push_back(u); 
            }
        }
    }
    if (!visited[t]) {
        return vector<u32>(); }
    vector<u32> result;
    for (u32 last = t; last < V; last = predecessor[last]) {
        result.push_back(last); }
    reverse(result.begin(), result.end());
    return result;
}

void FordFulkerson::increase_flow(const vector<u32>& path) {
    flow_size += 1;
    for (u32 i = 0; i < path.size() - 1; ++i) {
        residual[path[i]].erase(path[i+1]);
        residual[path[i+1]].insert(path[i]);
    }
}

u32 read_solve_case() {
    u32 N;
    cin >> N;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    unordered_map<string, unordered_set<u32>> sentences_with_word;
    for (u32 i = 0; i < N; ++i) {
        string l;
        getline(cin, l);
        istringstream lin(l);
        while (!lin.eof()) {
            string w;
            lin >> w;
            sentences_with_word[w].insert(i);
        }
    }
    u32 Nwords = sentences_with_word.size();
    Graph G(N + 2*Nwords);
    u32 wi = 0;
    for (auto& w_ss : sentences_with_word) {
        G[N + wi].insert(N + wi + 1);
        for (auto s : w_ss.second) {
            if (s != 1) {
                G[s].insert(N + wi); }
            if (s != 0) {
            G[N + wi + 1].insert(s); }
        }
        wi += 2;
    }
    return FordFulkerson(G, 0, 1).max_flow_size();
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
