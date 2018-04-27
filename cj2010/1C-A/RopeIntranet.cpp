#include <everything.h>

using namespace std;

int read_solve_case() {
    int N;
    cin >> N;
    vector<pair<int,int>> ws(N);
    for (int i = 0; i < N; ++i)
        cin >> ws[i].first >> ws[i].second;
    int intersections = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if ((ws[i].first - ws[j].first) * (ws[i].second - ws[j].second)
                    < 0) 
                intersections += 1;
        }
    }
    return intersections;
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
