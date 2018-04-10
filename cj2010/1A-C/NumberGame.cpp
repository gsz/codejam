#include <everything.h>

using namespace std;

constexpr double golden_ratio = (sqrt(5) + 1) / 2;
constexpr double inv_golden_ratio = (sqrt(5) - 1) / 2;

int intranges_overlap(int lo1, int hi1, int lo2, int hi2) {
    if (hi1 < lo2 || hi2 < lo1) {
        return 0;
    } else if (lo1 >= lo2 && lo1 <= hi2) {
        return min(hi1, hi2) - lo1 + 1;
    } else {
        return min(hi1, hi2) - lo2 + 1;
    }
}

u64 read_solve_case() {
    int A1, A2, B1, B2;
    cin >> A1 >> A2 >> B1 >> B2;
    u64 winning = 0;
    for (int a = A1; a <= A2; ++a) {
        int losing_B_lo = static_cast<int>(ceil(inv_golden_ratio * a));
        int losing_B_hi = static_cast<int>(floor(golden_ratio * a));
        winning += intranges_overlap(0, losing_B_lo - 1, B1, B2);
        winning += intranges_overlap(losing_B_hi + 1, 1000000, B1, B2);
    }
    return winning;
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
