#include <everything.h>

using namespace std;

string read_solve_case() {
    i64 N;
    int Pd, Pg;
    cin >> N >> Pd >> Pg;
    int numerator = Pd;
    int denominator = 100;
    while (numerator % 2 == 0 && denominator % 2 == 0) {
        numerator /= 2;
        denominator /= 2;
    }
    while (numerator % 5 == 0 && denominator % 5 == 0) {
        numerator /= 5;
        denominator /= 5;
    }
    if (N >= denominator && !(Pg == 0 && Pd != 0) && !(Pg == 100 && Pd != 100))
        return "Possible";
    return "Broken";
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
