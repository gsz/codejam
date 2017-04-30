#include <everything.h>

using namespace std;

long double read_solve_case() {
    u32 N, K;
    cin >> N >> K;
    assert(N == K);
    double U;
    cin >> U;
    vector<double> probs(N);
    for (u32 i = 0; i < N; ++i) {
        cin >> probs[i];
    }
    sort(probs.begin(), probs.end());
    u32 leveled = 1;
    for (leveled = 1; leveled < N; ++leveled) {
        if ((probs[leveled] - probs[leveled-1]) * leveled <= U) {
            U -= (probs[leveled] - probs[leveled-1]) * leveled;
            for (u32 j = 0; j < leveled; ++j)
                probs[j] = probs[leveled];
        } else {
            break;
        }
    }
    double share = U / leveled;
    for (u32 j = 0; j < leveled; ++j) 
        probs[j] += share;
    double best_prob_log = 0;
    for (auto ip = probs.begin(); ip != probs.end(); ++ip)
        best_prob_log += log(*ip);
    return exp(best_prob_log);
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cout << setprecision(9);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl;
    }
    return 0;
}

