#include <everything.h>

using namespace std;

struct Card {
    char c, s, t;
};

bool scoregt(const Card &c1, const Card &c2) {
    return c1.s > c2.s;
}

struct Gamestate {
    vector<Card> hand;
    vector<Card> deck;
    int score;
    u32 turns;
    Gamestate(int _score=0) : hand(), deck(), score(_score), turns(1) { }
};

Gamestate turn_bonus_closure(Gamestate &s) {
    if (s.turns == 0)
        return s;
    Gamestate res = s;
    vector<Card> newhand;
    for (u32 i = 0; i < res.hand.size(); ++i) {
        Card card = res.hand[i];
        if (card.t == 0) {
            newhand.push_back(card);
            continue;
        }
        res.score += card.s;
        res.turns += card.t - 1;
        while (card.c-- && !res.deck.empty()) {
            res.hand.push_back(res.deck.back());
            res.deck.pop_back();
        }
    }
    res.hand = move(newhand);
    return res;
}

int finalize_game(Gamestate &s) {
    sort(s.hand.begin(), s.hand.end(), scoregt);
    int final_score = s.score;
    auto cit = s.hand.begin();
    for (; cit != s.hand.end() && s.turns > 0; ++cit, --s.turns) {
        if (cit->c == 0) {
            final_score += cit->s;
        }
    }
    return final_score;
}

bool play_best_with_c(Gamestate &s, char c) {
    if (s.turns == 0)
        return false;
    int best_idx = -1;
    for (u32 i = 0; i < s.hand.size(); ++i) {
        if (s.hand[i].c != c)
            continue;
        if (best_idx == -1 || s.hand[i].s > s.hand[best_idx].s)
            best_idx = i;
    }
    if (best_idx == -1)
        return false;
    s.score += s.hand[best_idx].s;
    s.turns -= 1;
    while (c-- && !s.deck.empty()) {
        s.hand.push_back(s.deck.back());
        s.deck.pop_back();
    }
    s.hand[best_idx] = s.hand[s.hand.size()-1];
    s.hand.pop_back();
    return true;
}

int best_score(Gamestate &init) {
    int ncards = init.hand.size() + init.deck.size();
    vector<vector<Gamestate>> best_draws(
        ncards+1, vector<Gamestate>(ncards+1, Gamestate(INT_MIN)));
    // best_draws[i][j] -- best scoring draw of i 1c-cards and j 2c-cards
    best_draws[0][0] = turn_bonus_closure(init);
    for (int i = 0; i < ncards; ++i) {
        for (int j = 0; j < ncards; ++j) {
            if (i == 0 && j == 0)
                continue;
            Gamestate s_1c(INT_MIN), s_2c(INT_MIN);
            if (i != 0 && best_draws[i-1][j].score != INT_MIN) {
                s_1c = best_draws[i-1][j];
                if (!play_best_with_c(s_1c, 1)) {
                    s_1c.score = INT_MIN;
                } else {
                    s_1c = turn_bonus_closure(s_1c);
                }
            }
            if (j != 0 && best_draws[i][j-1].score != INT_MIN) {
                s_2c = best_draws[i][j-1];
                if (!play_best_with_c(s_2c, 2)) {
                    s_2c.score = INT_MIN;
                } else {
                    s_2c = turn_bonus_closure(s_2c);
                }
            }
            best_draws[i][j] = (s_1c.score > s_2c.score ? move(s_1c)
                                                        : move(s_2c));
        }
    }
    int best = INT_MIN;
    for (int i = 0; i < ncards; ++i) {
        for (int j = 0; j < ncards; ++j) {
            if (best_draws[i][j].score == INT_MIN)
                continue;
            best = max(best, finalize_game(best_draws[i][j]));
        }
    }
    return best;
}

int read_solve_case() {
    Gamestate initial;
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int c, s, t;
        cin >> c >> s >> t;
        initial.hand.push_back(Card{(char)c, (char)s, (char)t});
    }
    int M;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        int c, s, t;
        cin >> c >> s >> t;
        initial.deck.push_back(Card{(char)c, (char)s, (char)t});
    }
    reverse(initial.deck.begin(), initial.deck.end());
    return best_score(initial);
};

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl;
    }
    return 0;
}
