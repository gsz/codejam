#include <cassert>
#include <memory>
#include <ios>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

int remove_letter(unordered_map<char, int>& letters, const string& digit, 
                  char l) {
    int num_removed = letters[l];
    for (char c : digit) {
        letters[c] -= num_removed; }
    return num_removed;
}

string read_solve_case() {
    string S;
    cin >> S;
    vector<int> num_digits(10, 0);
    unordered_map<char, int> letters;
    for (char c : S) {
        letters[c] += 1; }
    num_digits[6] = remove_letter(letters, "SIX", 'X');
    num_digits[7] = remove_letter(letters, "SEVEN", 'S');
    num_digits[5] = remove_letter(letters, "FIVE", 'V');
    num_digits[4] = remove_letter(letters, "FOUR", 'F');
    num_digits[2] = remove_letter(letters, "TWO", 'W');
    num_digits[0] = remove_letter(letters, "ZERO", 'Z');
    num_digits[1] = remove_letter(letters, "ONE", 'O');
    num_digits[8] = remove_letter(letters, "EIGHT", 'G');
    num_digits[3] = remove_letter(letters, "THREE", 'T');
    num_digits[9] = remove_letter(letters, "NINE", 'I');
    string result;
    for (int d = 0; d <= 9; ++d) {
        while (num_digits[d]-- > 0) {
            result.push_back('0' + d); }
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

