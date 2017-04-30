#include <everything.h>

using namespace std;

string read_solve_case() {
    int N, R, O, Y, G, B, V;
    cin >> N >> R >> O >> Y >> G >> B >> V;
    assert(O == 0 && G == 0 && V == 0); // small dataset
    if (R > B + Y || abs(B-Y) > R)
        return "IMPOSSIBLE";
    string result;
    while (R > 1) {
        char surplus_char = B > Y ? 'B' : 'Y';
        int &surplus_count = B > Y ? B : Y;
        result.push_back('R');
        R--;
        result.push_back(surplus_char);
        surplus_count--;
    }
    if (R > 0)
        result.push_back('R');
    char surplus_char = B > Y ? 'B' : 'Y';
    int &surplus_count = B > Y ? B : Y;
    char other_char = B > Y ? 'Y' : 'B';
    if (B != Y) {
        result.push_back(surplus_char);
        surplus_count--;
    }
    while (surplus_count-- > 0) {
        result.push_back(other_char);
        result.push_back(surplus_char);
    }
    return result;
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

