#include <cassert>
#include <cmath>
#include <climits>
#include <limits>
#include <memory>
#include <ios>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <deque>
#include <list>
#include <queue>
#include <random>
#include <stack>
#include <tuple>
#include <map>
#include <set>
#include <unordered_map>
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
    if (L == 1) {
        for (int i = 0; i < N; ++i) {
            string word;
            cin >> word;
        }
        return "-";
    }
    unordered_set<string> words;
    unordered_set<char> col1, col2;
    for (int i = 0; i < N; ++i) {
        string word;
        cin >> word;
        col1.insert(word[0]);
        col2.insert(word[1]);
        words.insert(word);
    }
    string pw(2,' ');
    for (char c1 : col1) {
        for (char c2 : col2) {
            pw[0] = c1;
            pw[1] = c2;
            if (words.count(pw) == 0)
                return pw;
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
