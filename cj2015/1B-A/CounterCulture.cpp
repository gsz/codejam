#include <cassert>
#include <memory>
#include <ios>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

typedef unsigned long long uint64;
typedef unsigned int uint;

string bin(uint64 n) {
    string result;
    while (n > 0) {
        result.push_back(n & 1 ? '1' : '0');
        n >>= 1;
    }
    reverse(result.begin(), result.end());
    return result;
}

uint64 pow10(uint exp) {
    uint64 result = 1;
    for (auto c : bin(exp)) {
        result = result * result * (c == '1' ? 10 : 1);
    }
    return result;
}

uint64 moves_from_power_of_10(uint64 target) {
    string str_target = to_string(target);
    if (str_target.size() == 1) {
        return target - 1;
    }
    string half1(str_target.begin(), 
                 str_target.begin() + str_target.size() / 2);
    string half2(str_target.begin() + str_target.size() / 2,
                 str_target.end());
    if (stoull(half1) == pow10(half1.size() - 1)) {
        return stoll(half2);
    }
    reverse(half1.begin(), half1.end());
    if (stoull(half2) == 0) {
        auto ic = half1.begin();
        while (*ic == '0') {
            *ic++ = '9';
        }
        *ic = *ic - 1;
        return min(stoull(half1) + pow10(half2.size()), 
                   target - pow10(str_target.size()-1)); 
    }
    return stoull(half1) + stoull(half2); 
               
}

int read_solve_case() {
    uint64 N;
    cin >> N;
    string strN = to_string(N);
    uint64 moves = 1;
    uint num_digits = 1; 
    while (num_digits < strN.size()) {
        moves += moves_from_power_of_10(pow10(num_digits) - 1) + 1;
        num_digits += 1;
    }
    moves += moves_from_power_of_10(N);
    return moves;
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
