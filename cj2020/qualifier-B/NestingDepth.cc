#include <iostream>
#include <string>
#include <vector>

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

using namespace std;

string read_solve_case() {
    string S;
    cin >> S;
    string result;
    u32 cur_open = 0;
    for (char c : S) {
        u32 d = c - '0';
        if (d > cur_open) {
            result.append(d - cur_open, '(');
        } else if (d < cur_open) {
            result.append(cur_open - d, ')');
        }
        result.append(1, c);
        cur_open = d;
    }
    result.append(cur_open, ')');
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

