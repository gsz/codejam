#include <everything.h>

using namespace std;

struct Eratosthenes {
    vector<i64> ps;

    Eratosthenes(int upto);
};

Eratosthenes::Eratosthenes(int upto) {
    vector<bool> sieve(upto+1, true);
    int max_relevant = static_cast<int>(floor(sqrt(upto)));
    for (int p = 2; p <= max_relevant; ++p) {
        if (!sieve[p])
            continue;
        for (int n = 2 * p; n <= upto; n += p)
            sieve[n] = false;
    }
    for (int n = 2; n <= upto; ++n) {
        if (sieve[n])
            ps.push_back(n);
    }
}

Eratosthenes primes(1000000);

i64 normalize(i64 n, i64 M) {
    return (n + M) % M;
}

i64 modular_inverse(i64 n, i64 M) {
    i64 A = n, B = M;
    i64 x1 = 1, y1 = 0, x2 = 0, y2 = 1;
    while (B > 0) {
        i64 q = A / B;
        i64 r = A % B;
        i64 nx2 = x1 - q * x2;
        i64 ny2 = y1 - q * y2;
        A = B;
        x1 = x2;
        y1 = y2;
        B = r;
        x2 = nx2;
        y2 = ny2;
    }
    return normalize(x1, M);
}


string read_solve_case() {
    int D, K;
    cin >> D >> K;
    vector<i64> S(K);
    for (int k = 0; k < K; ++k)
        cin >> S[k];
    if (K == 1 || (K == 2 && S[0] != S[1])) {
        return "I don't know.";
    } else if (S[0] == S[1]) {
        return to_string(S[1]);
    }
    i64 maxP = 1;
    while (D-- > 0)
        maxP *= 10;
    i64 maxS = *max_element(S.begin(), S.end());
    vector<i64> possible_Ps;
    copy_if(primes.ps.begin(), primes.ps.end(), back_inserter(possible_Ps),
            [=](i64 p) { return p <= maxP && p > maxS; });
    unordered_set<i64> candidates;
    for (i64 P : possible_Ps) {
        i64 A = normalize(S[2] - S[1], P) * 
                modular_inverse(normalize(S[1] - S[0], P), P) % P;
        i64 B = normalize(S[1] - (A * S[0] % P), P);
        bool matches = true;
        for (u32 i = 1; i < S.size(); ++i) {
            if ((S[i-1] * A + B) % P != S[i])
                matches = false;
        }
        if (matches) {
            candidates.insert((S.back() * A + B) % P);
            if (candidates.size() > 1)
                return "I don't know.";
        }
    }
    return to_string(*candidates.begin());
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
