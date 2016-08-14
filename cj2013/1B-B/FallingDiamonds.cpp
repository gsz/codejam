#include <everything.h>

using namespace std;

const int INFTY = 100'000'000; // approximately 

int layer_size(int layer_idx) {
    return layer_idx < 1000 ? layer_idx * 4 + 1 : INFTY;
}

int cumulative_layer_size(int num_layers) {
    return (num_layers < 1000 ? num_layers + 2 * (num_layers) * (num_layers - 1)
                              : INFTY);
}

class BinsumCache {
    vector<vector<double>> data;
public:
    BinsumCache(int max_args);
    double operator()(int n, int k) { return data[n][k]; }
};

BinsumCache::BinsumCache(int max_args): data(max_args+1) {
    for (int n = 0; n <= max_args; ++n) {
        data[n].resize(n+1);
        data[n][0] = 1;
        for (int k = 1; k < n; ++k) {
            data[n][k] = data[n-1][k-1] + data[n-1][k];
        }
        data[n][n] = data[n][n-1] + 1;
    }
}

BinsumCache partial_binomial_sum(2000);

double read_solve_case() {
    int N, X, Y;
    cin >> N >> X >> Y;
    int layer = (abs(X) + Y) / 2;
    int diamonds_in_layer = N - cumulative_layer_size(layer);
    if (Y == layer * 2) {
        return diamonds_in_layer >= layer_size(layer) ? 1.0 : 0.0; }
    int side_height = 2 * layer;
    int diamonds_needed = Y + 1;
    if (diamonds_in_layer < diamonds_needed) {
        return 0.0; }
    if (diamonds_in_layer >= side_height + diamonds_needed) {
        return 1.0; }
    double binsum = partial_binomial_sum(diamonds_in_layer, diamonds_needed-1);
    return 1 - binsum / pow(2, diamonds_in_layer);
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
