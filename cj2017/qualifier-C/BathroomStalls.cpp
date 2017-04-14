#include <everything.h>

using namespace std;

string read_solve_case() {
    u64 N, K;
    cin >> N >> K;
    u64 smaller_intervals = 1, bigger_intervals = 0;
    u64 smaller_size = N;
    u64 final_size;
    while (true) {
        if (K <= bigger_intervals) {
            final_size = smaller_size + 1;
            break;
        }
        K -= bigger_intervals;
        if (K <= smaller_intervals) {
            final_size = smaller_size;
            break;
        }
        K -= smaller_intervals;
        if (smaller_size % 2 == 0) {
            bigger_intervals = smaller_intervals + 2 * bigger_intervals;
        } else {
            smaller_intervals = 2 * smaller_intervals + bigger_intervals;
        }
        smaller_size = (smaller_size - 1) / 2;
    }
    ostringstream result;
    result << final_size / 2 << ' ' << (final_size - 1) / 2;
    return result.str();
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

