#include <everything.h>

using namespace std;

const u32 PRIMES_UPTO = 1000000;
const u64 MAXN = 1000000000000;

struct Eratosthenes {
    vector<u64> ps;
    vector<u64> powers;

    Eratosthenes();
};

Eratosthenes::Eratosthenes() {
    u64 maxfactor = static_cast<u64>(ceil(sqrt(PRIMES_UPTO)));
    vector<bool> nums(PRIMES_UPTO+1, true);
    for (u64 i = 2; i <= maxfactor; ++i) {
        if (!nums[i])
            continue;
        for (u32 j = 2 * i; j <= PRIMES_UPTO; j += i)
            nums[j] = false;
    }
    for (u64 i = 2; i <= PRIMES_UPTO; ++i) {
        if (nums[i]) {
            ps.push_back(i);
            u64 pow = i*i;
            while (pow <= MAXN) {
                powers.push_back(pow);
                pow *= i;
            }
        }
    }
    powers.push_back(1);
    sort(powers.begin(), powers.end());
}

Eratosthenes primes;

u32 read_solve_case() {
    u64 N;
    cin >> N;
    if (N == 1)
        return 0;
    u32 res = (lower_bound(primes.powers.begin(), primes.powers.end(), N)
               - primes.powers.begin());
    if (primes.powers[res] == N)
        res += 1;
    return res;
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
