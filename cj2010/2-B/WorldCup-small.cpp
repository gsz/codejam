#include <everything.h>

using namespace std;

int read_solve_case() {
    int P;
    cin >> P;
    vector<bool> tickets(1<<P, false);
    for (int i = 0; i < 1<<P; ++i) {
        int skip;
        cin >> skip;
        int match = ((1<<P) + i) / 2;
        while (skip--)
            match /= 2;
        for (; match >= 1; match /= 2)
            tickets[match] = true;
    }
    for (int i = 0; i < (1<<P) - 1; ++i) {
        int _;
        cin >> _;
    }
    return count(tickets.begin(), tickets.end(), true);
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
