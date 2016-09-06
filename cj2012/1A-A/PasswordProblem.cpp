#include <everything.h>

using namespace std;

double read_solve_case() {
    int A, B;
    cin >> A >> B;
    vector<double> p(A);
    for (int i = 0; i < A; ++i) {
        cin >> p[i]; }
    double best_expectation = 2 + B;
    double prob_correct = 1;
    for (int i = 1; i <= A; ++i) {
        prob_correct *= p[i-1];
        int min_keystrokes = 2 * (A - i) + B - A + 1;
        double expectation = min_keystrokes + (1 - prob_correct) * (B + 1);
        best_expectation = min(expectation, best_expectation);
    }
    return best_expectation;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(8);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl;
    }
    return 0;
}

