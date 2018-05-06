#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

string read_solve_case() {
    int N, L;
    cin >> N >> L;
    unordered_set<string> words;
    vector<unordered_set<char>> cols(L);
    for (int i = 0; i < N; ++i) {
        string word;
        cin >> word;
        words.insert(word);
        for (int j = 0; j < L; ++j)
            cols[j].insert(word[j]);
    }
    vector<vector<char>> colchars(L);
    for (int j = 0; j < L; ++j)
        copy(cols[j].begin(), cols[j].end(), back_inserter(colchars[j]));
    vector<u32> colidxs(L, 0);
    for (int n = 0; n < N + 1; ++n) {
        string word(L, '.');
        for (int j = 0; j < L; ++j)
            word[j] = colchars[j][colidxs[j]];
        if (words.count(word) == 0)
            return word;
        bool carry = true;
        for (int j = 0; j < L && carry; ++j) {
            colidxs[j] += 1;
            carry = (colidxs[j] == colchars[j].size());
            if (carry)
                colidxs[j] = 0;
        }
    }
    return "-";
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
