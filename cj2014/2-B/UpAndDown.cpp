#include <everything.h>

using namespace std;

int sgn(int n) {
    return n > 0 ? 1 : (n < 0 ? -1 : 0);
}

int count_swaps(int pos, vector<int>& nums, int max_pos, bool opposite) {
    int inc = pos > max_pos ? 1 : -1;
    inc *= opposite ? -1 : 1;
    int growth_direction = -inc; // sign of val difference relative to pos diff
    int swaps = 0;
    for (int i = max_pos + inc; i >= 0 && (u32)i < nums.size(); i += inc) {
        if (pos == i) {
            continue; }
        if (sgn(nums[i] - nums[pos]) * sgn(i - pos) * growth_direction < 0) {
            swaps += 1; }
    }
    return swaps;
}

int read_solve_case() {
    int N;
    cin >> N;
    vector<int> A(N);
    int max_num = 0, max_pos;
    for (int n = 0; n < N; ++n) {
        cin >> A[n]; 
        if (A[n] > max_num) {
            max_num = A[n];
            max_pos = n;
        }
    }
    int total_swaps = 0;
    for (int n = max_pos+1; n < N; ++n) {
        int right_swaps = count_swaps(n, A, max_pos, false);
        int left_swaps = count_swaps(n, A, max_pos, true);
        if (left_swaps + n - max_pos < right_swaps) {
            total_swaps += n - max_pos;
            int val = A[n];
            copy_backward(A.begin() + max_pos, A.begin() + n,
                          A.begin() + n + 1);
            A[max_pos++] = val;
        }
    }
    for (int n = max_pos-1; n >= 0; --n) {
        int right_swaps = count_swaps(n, A, max_pos, true);
        int left_swaps = count_swaps(n, A, max_pos, false);
        if (right_swaps + max_pos - n < left_swaps) {
            total_swaps += max_pos - n;
            int val = A[n];
            copy(A.begin() + n + 1, A.begin() + max_pos + 1,
                 A.begin() + n);
            A[max_pos--] = val;
        }
    }
    int final_swaps = 0;
    for (int n = max_pos+1; n < N; ++n) {
        final_swaps += count_swaps(n, A, max_pos, false); }
    for (int n = max_pos - 1; n >= 0; --n) {
        final_swaps += count_swaps(n, A, max_pos, false); }
    total_swaps += final_swaps / 2;
    return total_swaps;
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

