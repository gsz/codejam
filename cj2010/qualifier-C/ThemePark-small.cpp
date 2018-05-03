#include <everything.h>

using namespace std;

int read_solve_case() {
    int R, k, N;
    cin >> R >> k >> N;
    vector<int> g(N);
    for (int i = 0; i < N; ++i)
        cin >> g[i];
    int earnings = 0;
    int queue_start = 0;
    while (R-- > 0) {
        int i = queue_start;
        int space_remaining = k - g[i];
        earnings += g[i];
        for (i = (i + 1) % N; i != queue_start; i = (i + 1) % N) {
            if (space_remaining < g[i]) 
                break;
            space_remaining -= g[i];
            earnings += g[i];
        }
        queue_start = i;
    }
    return earnings;
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
