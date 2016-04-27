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

typedef unordered_map<char, size_t> FreqDict;
typedef unsigned int uint;

size_t max_overlap(string& word) {
    vector<size_t> prefix_table(word.size()+1, 0);
    for (int i = 2; i < prefix_table.size(); ++i) {
        int j = i-1;
        while (j != 0 && word[prefix_table[j]] != word[i-1]) {
            j = prefix_table[j];
        }
        if (j == 0) {
            prefix_table[i] = word[0] == word[i-1] ? 1 : 0;
        } else {
            prefix_table[i] = prefix_table[j] + 1;
        }
    }
    return prefix_table[prefix_table.size()-1];
}

double read_solve_case() {
    uint K, L, S;
    cin >> K >> L >> S;
    string keyboard, target;
    cin >> keyboard >> target;
    FreqDict freqs;
    for (char c : keyboard) {
        freqs[c] += 1;
    }
    for (char c : target) {
        if (!freqs.count(c)) {
            return 0.0;
        }
    }
    double target_prob = 1.0;
    for (char c : target) {
        target_prob *= (double)freqs[c] / keyboard.size();
    }
    uint max_needed_bananas = 1 + (S - L) / (L - max_overlap(target));
    double expected_bananas = target_prob * (S - L + 1);
    return max_needed_bananas - expected_bananas;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    cout << showpoint << setprecision(10) << fixed;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl;
    }
    return 0;
}

