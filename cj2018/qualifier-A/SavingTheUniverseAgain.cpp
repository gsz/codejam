#include <iostream>
#include <vector>

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

using namespace std;

string read_solve_case() {
    u64 D;
    string prg;
    cin >> D >> prg;
    u64 power = 1, dmg = 0;
    for (char c : prg) {
        if (c == 'C') {
            power *= 2;
        } else {
            dmg += power;
        }
    }
    u32 changes = 0;
    u32 i = prg.size() - 1;
    while (dmg > D) {
        if (prg[i] == 'C' && i < prg.size() - 1 && prg[i+1] == 'S') {
            dmg -= power / 2;
            swap(prg[i], prg[i+1]);
            changes += 1;
            i += 1;
        } else if (i == 0) {
            break;
        } else if (prg[i] == 'C') {
            power = power / 2;
            i -= 1;
        } else {
            i -= 1;
        }
    }
    return (dmg > D ? "IMPOSSIBLE" : to_string(changes));
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
