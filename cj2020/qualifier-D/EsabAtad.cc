#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

using namespace std;

bool get_response() {
    char response;
    cin >> response;
    if (response == 'N')
        exit(1);
    return response == '1';
}

void solve_case(int B) {
    vector<bool> bits(B);
    int known = 0;
    int queries = 0;
    int sym_canary{-1}, asym_canary{-1};
    bool response;
    while (known < B) {
        if (queries > 0 && queries % 10 == 0) {
            cout << (sym_canary != -1 ? sym_canary + 1 : 1) << endl;
            response = get_response();
            if (sym_canary != -1 && bits[sym_canary] != response)
                transform(bits.begin(), bits.end(), bits.begin(),
                          [](auto b) { return !b; });
            cout << (asym_canary != -1 ? asym_canary + 1 : 1) << endl;
            response = get_response();
            if (asym_canary != -1 && bits[asym_canary] != response)
                reverse(bits.begin(), bits.end());
            queries += 2;
        }
        cout << known + 1 << endl;
        bits[known] = get_response();
        cout << B - known << endl;
        bits[B - 1 - known] = get_response();
        if (bits[known] == bits[B - 1 - known] && sym_canary == -1) {
            sym_canary = known;
        } else if (bits[known] != bits[B - 1 - known] && asym_canary == -1) {
            asym_canary = known;
        }
        known += 2;
        queries += 2;
    }
    string result(B, '*');
    transform(bits.begin(), bits.end(), result.begin(), 
              [](auto b) { return '0' + b; });
    cout << result << endl;
    char final_resp;
    cin >> final_resp;
    if (final_resp != 'Y')
        exit(2);
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T, B;
    cin >> T >> B;
    for (int ci = 1; ci <= T; ++ci) {
        solve_case(B);
    }
    return 0;
}

