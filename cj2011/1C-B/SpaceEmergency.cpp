#include <everything.h>

using namespace std;

u64 read_solve_case() {
    u64 L, t, N, C;
    cin >> L >> t >> N >> C;
    vector<u32> dists(N);
    for (u32 i = 0; i < C; ++i)
        cin >> dists[i];
    for (u32 i = C; i < N; ++i)
        dists[i] = dists[i % C];
    reverse(dists.begin(), dists.end());
    u64 hours = 0;
    while (!dists.empty()) {
        if (hours + 2*dists.back() < t) {
            hours += 2*dists.back();
            dists.pop_back();
        } else {
            dists.back() -= (t - hours) / 2;
            hours = t;
            break;
        }
    }
    sort(dists.begin(), dists.end());
    while (L-- != 0 && !dists.empty()) {
        hours += dists.back();
        dists.pop_back();
    }
    while (!dists.empty()) {
        hours += 2*dists.back();
        dists.pop_back();
    }
    return hours;
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
