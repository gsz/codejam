#include <everything.h>

using namespace std;

void read_solve_case_print() {
    int N;
    cin >> N;
    vector<string> sched(N);
    vector<int> wins(N, 0), games(N, 0);
    vector<double> rpi(N), owp(N);
    vector<unordered_set<int>> opponents(N);
    for (int i = 0; i < N; ++i) {
        cin >> sched[i];
        for (u32 j = 0; j < sched[i].size(); ++j) {
            if (sched[i][j] != '.') {
                opponents[i].insert(j);
                games[i] += 1;
            }
            if (sched[i][j] == '1')
                wins[i] += 1;
        }
        rpi[i] = 0.25 * (double)wins[i] / games[i];
    }
    for (int i = 0; i < N; ++i) {
        double owp_sum = 0;
        for (int j : opponents[i]) {
            int owins = wins[j] - (sched[j][i] == '1');
            owp_sum += (double)owins / (games[j] - 1);
        }
        owp[i] = owp_sum / opponents[i].size();
        rpi[i] += 0.5 * owp[i];
    }
    for (int i = 0; i < N; ++i) {
        double oowp_sum = 0;
        for (int j : opponents[i])
            oowp_sum += owp[j];
        rpi[i] += 0.25 * oowp_sum / opponents[i].size();
    }
    for (double x : rpi)
        cout << x << endl;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    cout << setprecision(8) << fixed;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << endl;
        read_solve_case_print();
    }
    return 0;
}

