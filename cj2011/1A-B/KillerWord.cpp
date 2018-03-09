#include <everything.h>

using namespace std;

const int MAX_WORDLEN = 10;
const int LETTERMASK_LIMIT = 1 << MAX_WORDLEN;

int letter_mask(char c, string &word) {
    int mask = 0;
    for (u32 j = 0; j < word.length(); ++j) {
        if (word[j] == c)
            mask |= 1 << j;
    }
    return mask;
}

struct Instance {
    int N, M;
    vector<string> words, lperms;
    vector<unordered_set<int>> words_of_length{MAX_WORDLEN+1};

    void read();
    int subpartition(vector<unordered_set<int>> &part, 
                     vector<int> &scores, int idx, char c);
    int best_word(string &lperm);
    void solve_print();
};

void Instance::read() {
    cin >> N >> M;
    words.resize(N);
    lperms.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> words[i];
        words_of_length[words[i].length()].insert(i);
    }
    for (int m = 0; m < M; ++m)
        cin >> lperms[m];
}

int Instance::subpartition(vector<unordered_set<int>> &part, 
                           vector<int> &scores, int idx, char c) {
    int score = scores[idx];
    unordered_set<int> &block = part[idx];
    unordered_map<int, unordered_set<int>> mask_subblocks;
    for (int wi : block) {
        int mask = letter_mask(c, words[wi]);
        mask_subblocks[mask].insert(wi);
    }
    bool score_up = mask_subblocks.count(0) && mask_subblocks.size() > 1;
    auto msb_i = mask_subblocks.begin();
    part[idx] = move(msb_i->second);
    scores[idx] += (msb_i->first == 0 && score_up);
    for (++msb_i; msb_i != mask_subblocks.end(); ++msb_i) {
        part.push_back(move(msb_i->second));
        scores.push_back(score + (msb_i->first == 0 && score_up));
    }
    return score + score_up;
}

int Instance::best_word(string &lperm) {
    vector<unordered_set<int>> dict_partition;
    vector<int> scores;
    for (auto &ws : words_of_length) {
        if (!ws.empty()) {
            dict_partition.push_back(ws);
            scores.push_back(0);
        }
    }
    int best_score = 0;
    for (char c : lperm) {
        int num_blocks = dict_partition.size();
        for (int i = 0; i < num_blocks; ++i)
            best_score = max(best_score, 
                             subpartition(dict_partition, scores, i, c));
    }
    int earliest_best_word = N-1;
    for (u32 i = 0; i < dict_partition.size(); ++i) {
        if (scores[i] == best_score)
            earliest_best_word = min(*min_element(dict_partition[i].begin(),
                                                  dict_partition[i].end()),
                                     earliest_best_word);
    }
    return earliest_best_word;
}

void Instance::solve_print() {
    for (int m = 0; m < M; ++m) {
        int bestw = best_word(lperms[m]);
        cout << words[bestw];
        if (m < M-1)
            cout << ' ';
    }
}

void read_solve_print_case() {
    Instance inst;
    inst.read();
    inst.solve_print();
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": "; 
        read_solve_print_case();
        cout << endl;
    }
    return 0;
}
