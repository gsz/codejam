#include <everything.h>

using namespace std;

struct Instance {
    int N, M;
    vector<pair<int,int>> edges;
    vector<vector<int>> area_verts;
    vector<unordered_set<int>> areas_of_vert;
    vector<vector<int>> area_neighbors;

    void split_by_edge(int v1, int v2);
    void calc_neighbors();
    void read();
    void solve_print();
};

void Instance::read() {
    cin >> N >> M;
    vector<int> vs1(M), vs2(M);
    for (int i = 0; i < M; ++i)
        cin >> vs1[i];
    for (int i = 0; i < M; ++i)
        cin >> vs2[i];
    for (int i = 0; i < M; ++i)
        edges.push_back(make_pair(vs1[i], vs2[i]));
    area_verts.emplace_back();
    areas_of_vert.resize(N+1);
    for (int i = 1; i <= N; ++i) {
        area_verts[0].push_back(i);
        areas_of_vert[i].insert(0);
    }
    for (int i = 0; i < M; ++i)
        split_by_edge(vs1[i], vs2[i]);
    calc_neighbors();
}

void Instance::split_by_edge(int v1, int v2) {
    int aidx = *find_if(areas_of_vert[v1].begin(), areas_of_vert[v1].end(),
                        [&](int a) { return areas_of_vert[v2].count(a); });
    int newaidx = area_verts.size();
    area_verts.emplace_back();
    vector<int> &verts = area_verts[aidx];
    vector<int> &newverts = area_verts[newaidx];
    vector<int> verts2;
    int i = (find(verts.begin(), verts.end(), v1)
             - verts.begin());
    for (; verts[i] != v2; i = (i + 1) % verts.size())
        verts2.push_back(verts[i]);
    verts2.push_back(v2);
    for (; verts[i] != v1; i = (i + 1) % verts.size()) {
        newverts.push_back(verts[i]);
        areas_of_vert[verts[i]].erase(aidx);
        areas_of_vert[verts[i]].insert(newaidx);
    }
    newverts.push_back(v1);
    areas_of_vert[v2].insert(aidx);
    areas_of_vert[v1].insert(newaidx);
    verts = move(verts2);
}

void Instance::calc_neighbors() {
    area_neighbors.resize(area_verts.size());
    for (auto edge : edges) {
        int v1, v2;
        tie(v1, v2) = edge;
        auto a1it = find_if(areas_of_vert[v1].begin(), areas_of_vert[v1].end(),
                            [&](int a) { return areas_of_vert[v2].count(a); });
        int a1 = *a1it;
        auto a2it = find_if(++a1it, areas_of_vert[v1].end(),
                            [&](int a) { return areas_of_vert[v2].count(a); });
        int a2 = *a2it;
        area_neighbors[a1].push_back(a2);
        area_neighbors[a2].push_back(a1);
    }
}

void Instance::solve_print() {
    int numcolors = N;
    for (auto &avs : area_verts)
        numcolors = min(numcolors, static_cast<int>(avs.size()));
    unordered_set<int> colors;
    for (int i = 1; i <= numcolors; ++i)
        colors.insert(i);
    vector<int> color_of_vert(N+1, 0);
    stack<int> aqueue;
    unordered_set<int> queued;
    aqueue.push(0);
    queued.insert(0);
    while (!aqueue.empty()) {
        int aidx = aqueue.top();
        aqueue.pop();
        vector<int> &verts = area_verts[aidx];
        unordered_set<int> missing_colors = colors;
        for (int v : verts) {
            if (color_of_vert[v])
                missing_colors.erase(color_of_vert[v]);
        }
        vector<int> colors_to_fill(missing_colors.begin(), 
                                   missing_colors.end());
        for (u32 i = 0; i < verts.size(); ++i) {
            if (color_of_vert[verts[i]]) 
                continue;
            int color;
            if (!colors_to_fill.empty()) {
                color = colors_to_fill.back();
                colors_to_fill.pop_back();
            } else {
                color = 1;
                if (color_of_vert[verts[(i+1) % verts.size()]] == color
                        || color_of_vert[verts[(i-1) % verts.size()]] == color)
                    color = 2;
                if (color_of_vert[verts[(i+1) % verts.size()]] == color
                        || color_of_vert[verts[(i-1) % verts.size()]] == color)
                    color = 3;
            }
            color_of_vert[verts[i]] = color;
        }
        for (int aidx2 : area_neighbors[aidx]) {
            if (queued.count(aidx2))
                continue;
            aqueue.push(aidx2);
            queued.insert(aidx2);
        }
    }
    cout << numcolors << endl;
    for (int i = 1; i <= N; ++i) {
        cout << color_of_vert[i];
        if (i != N)
            cout << ' ';
    }
    cout << endl;
}

void read_solve_print_case() {
    Instance inst;
    inst.read();
    inst.solve_print();
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": ";
        read_solve_print_case();
    }
    return 0;
}
