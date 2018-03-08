#include <everything.h>

using namespace std;

string read_solve_case() {
    int N;
    cin >> N;
    vector<int> d(N+1), l(N+1);
    for (int i = 0; i < N; ++i)
        cin >> d[i] >> l[i];
    cin >> d[N];
    l[N] = 0;
    vector<int> best_range(N+1, 0), last_reached_l(N+1), last_reached_r(N+1);
    for (int i = 0; i < N + 1; ++i) {
        last_reached_l[i] = i;
        last_reached_r[i] = i;
    }
    best_range[0] = d[0];
    queue<int> q;
    vector<bool> in_queue(N+1, false);
    q.push(0);
    in_queue[0] = true;
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        in_queue[i] = false;
        auto starti = lower_bound(d.begin(), d.end(), d[i] - best_range[i]);
        auto endi = upper_bound(starti, d.end(), d[i] + best_range[i]);
        for (int j = starti - d.begin(); j < endi - d.begin(); ++j) {
            if (j >= last_reached_l[i] && j <= last_reached_r[i]) {
                j = last_reached_r[i];
                continue;
            }
            if (j == N)
                return "YES";
            if (best_range[j] >= min(abs(d[i] - d[j]), l[j]))
                continue;
            best_range[j] = min(abs(d[i] - d[j]), l[j]);
            if (!in_queue[j]) {
                q.push(j);
                in_queue[j] = true;
            }
        }
        last_reached_l[i] = starti - d.begin();
        last_reached_r[i] = endi - 1 - d.begin();
    }
    return "NO";
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
