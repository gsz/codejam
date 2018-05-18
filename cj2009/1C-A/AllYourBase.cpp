#include <everything.h>

using namespace std;

u64 read_solve_case() {
    string input;
    cin >> input;
    unordered_map<char, int> coding;
    int next_digit = 0;
    for (char c : input) {
        if (coding.count(c))
            continue;
        coding[c] = next_digit++;
        if (coding[c] == 0 || coding[c] == 1)
            coding[c] = 1 - coding[c];
    }
    u64 base = max(next_digit, 2);
    u64 num = 0;
    for (char c : input) 
        num = num * base + coding[c];
    return num;
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
