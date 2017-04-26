#include <everything.h>

using namespace std;

string read_solve_case() {
    u32 N;
    cin >> N;
    vector<int> scores(N);
    int score_sum = 0;
    for (u32 i = 0; i < N; ++i) {
        cin >> scores[i];
        score_sum += scores[i];
    }
    ostringstream res_stream;
    for (u32 i = 0; i < N; ++i) {
        int score = scores[i];
        vector<int> other(scores); 
        other.erase(other.begin()+i);
        sort(other.begin(), other.end());
        double min_votes = 1;
        u32 num_other = 0;
        int equalized = scores[i];
        int pts_to_equalize = 0;
        for (auto is = other.begin(); is != other.end(); ++is) {
            int pts_to_overtake = max(0, *is - score);
            if (*is > score) {
                pts_to_equalize += num_other * (*is - equalized);
                equalized = *is;
            } else {
                pts_to_equalize += score - *is;
            }
            num_other += 1;
            double votes_to_overtake = (double)pts_to_overtake / score_sum;
            double votes_to_equalize = (double)pts_to_equalize / score_sum;
            double votes_to_survive = (votes_to_overtake +
                max(0.0, 1 - votes_to_overtake - votes_to_equalize) / 
                (num_other + 1));
            min_votes = min(votes_to_survive, min_votes);
        }
        res_stream << 100 * min_votes << ' ';
    }
    string res = res_stream.str();
    res.pop_back(); // trailing space
    return res;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cout << setprecision(8);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl;
    }
    return 0;
}
