#include <everything.h>

using namespace std;

u32 read_solve_case(u32 L, unordered_set<string> &dict) {
    string rawpat;
    cin >> rawpat;
    vector<unordered_set<char>> pattern(L);
    u32 raw_idx = 0, pidx = 0;
    while (raw_idx < rawpat.size()) {
        if (rawpat[raw_idx] == '(') {
            while (rawpat[++raw_idx] != ')')
                pattern[pidx].insert(rawpat[raw_idx]); 
        } else {
            pattern[pidx].insert(rawpat[raw_idx]);
        }
        pidx += 1;
        raw_idx += 1;
    }
    int matching_words = dict.size();
    for (const string &w : dict) {
        for (u32 i = 0; i < L; ++i) {
            if (pattern[i].count(w[i]) == 0) {
                matching_words -= 1;
                break;
            }
        }
    }
    return matching_words;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    u32 L, D, N;
    cin >> L >> D >> N;
    unordered_set<string> dict;
    for (u32 i = 0; i < D; ++i) {
        string w;
        cin >> w;
        dict.insert(w);
    }
    for (u32 ci = 1; ci <= N; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case(L, dict) << endl;
    }
    return 0;
}
