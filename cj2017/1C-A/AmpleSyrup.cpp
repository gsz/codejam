#include <everything.h>

using namespace std;

struct Pancake {
    double R, H;
    double side;
    Pancake(double R_, double H_): R(R_), H(H_), side(H * 2 * M_PI * R) { }
};

bool cmp_R(Pancake &p1, Pancake &p2) {
    return p1.R < p2.R;
}

bool cmp_side_area(Pancake &p1, Pancake &p2) {
    return p1.side < p2.side;
}

double read_solve_case() {
    u32 N, K;
    cin >> N >> K;
    vector<Pancake> ps;
    for (u32 i = 0; i < N; ++i) {
        double R, H;
        cin >> R >> H;
        ps.push_back(Pancake(R, H));
    }
    sort(ps.begin(), ps.end(), cmp_R);
    double best_area = 0;
    for (u32 i = K-1; i < N; ++i) {
        double total = ps[i].side + M_PI * ps[i].R * ps[i].R;
        vector<Pancake> ps2(ps.begin(), ps.begin()+i);
        sort(ps2.begin(), ps2.end(), cmp_side_area);
        for (u32 j = i - (K - 1); j < i; ++j)
            total += ps2[j].side;
        best_area = max(total, best_area);
    }
    return best_area;
}


int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cout << setprecision(9);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl;
    }
    return 0;
}

