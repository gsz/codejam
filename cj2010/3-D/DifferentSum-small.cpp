#include <everything.h>

using namespace std;

const u64 MOD = 1'000'000'007;

struct Variations {
    vector<vector<u64>> vals;

    Variations(u64 maxn);
    u64 operator()(u64 n, u64 k) { return vals[n][k]; }
};

Variations::Variations(u64 maxn) : vals(maxn+1) {
    vals[0].resize(1, 1);
    for (u64 n = 1; n <= maxn; ++n) {
        vals[n].resize(n+1, 1);
        u64 v = 1;
        for (u64 k = 1; k <= n; ++k) {
            v *= (n - k + 1);
            vals[n][k] = v;
        }
    }
}

Variations variations(10);

struct Instance {
    int B;
    vector<int> sum_digits;

    u64 num_cryptarithms(u32 pos, u64 last_setsize, int carry, 
                         int lastset);
};

string binary(int n) {
    string result;
    while (n > 0) {
        result.push_back('0' + (n & 1));
        n >>= 1;
    }
    reverse(result.begin(), result.end());
    return result;
}

inline string dbg_indent(int n) {
    return string(n*4, ' ');
}

// Recursively enumerate all sets of digits in different columns
u64 Instance::num_cryptarithms(u32 pos, u64 last_setsize, int carry, 
                               int lastset) {
    bool bottom_call = pos + 1 == sum_digits.size();
    bool last_haszero = (lastset & 1);
    int target = sum_digits[pos];
    if (bottom_call && target < carry)
        return 0;
    if (bottom_call && target == carry)
        return !last_haszero;
    u64 num = 0;
    int max_digit = bottom_call ? (target - carry) : (B - 1);
    for (int dset = 1; dset < (1 << (max_digit + 1)); ++dset) {
        int setsum = carry;
        u64 setsize = 0;
        for (int dig = 0; dig <= max_digit; ++dig) {
            if (dset & (1 << dig)) {
                setsum += dig;
                setsize += 1;
            }
        }
        if (setsum % B != target || setsize > last_setsize)
            continue;
        u64 arrangements;
        if (pos == 0) {
            arrangements = 1;
        } else if (last_haszero) {
            arrangements = setsize * variations(last_setsize - 1, setsize - 1);
        } else {
            arrangements = variations(last_setsize, setsize);
        } 
        if (bottom_call) {
            if (setsum >= B || (dset & 1) != 0)
                continue;
            num = (num + arrangements) % MOD;
        } else {
            u64 recnum = num_cryptarithms(pos+1, setsize, setsum / B, dset);
            num = (num + recnum * arrangements) % MOD;
        }
    }
    return num;
}

u64 read_solve_case() {
    Instance inst;
    int N, B;
    cin >> N >> B;
    inst.B = B;
    while (N > 0) {
        inst.sum_digits.push_back(N % B);
        N /= B;
    }
    return inst.num_cryptarithms(0, B, 0, 0);
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
