#include <everything.h>

using namespace std;

double read_solve_case() {
    double X, S, R, t; 
    int N;
    cin >> X >> S >> R >> t >> N;
    vector<pair<double, double>> segments(N+1); // speed, length
    double walkway_totallen = 0;
    for (int i = 0; i < N; ++i) {
        int B, E, w;
        cin >> B >> E >> w;
        walkway_totallen += E - B;
        segments[i].first = w;
        segments[i].second = E - B;
    }
    segments[N] = make_pair(0, X - walkway_totallen);
    sort(segments.begin(), segments.end());
    double time = 0;
    for (auto &seg : segments) {
        double len, w;
        tie(w, len) = seg;
        if (t >= len / (R + w)) {
            time += len / (R + w);
            t -= len / (R + w);
        } else if (t > 0) {
            time += t + (len - t * (R + w)) / (S + w);
            t = 0;
        } else {
            time += len / (S + w);
        }
    }
    return time;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    cout << setprecision(7) << fixed;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl;
    }
    return 0;
}
