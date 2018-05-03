#include <everything.h>

using namespace std;

constexpr double PI = acos(-1);

double dist(pair<double, double> p1, pair<double, double> p2) {
    double dx = p2.first - p1.first;
    double dy = p2.second - p1.second;
    return sqrt(dx*dx + dy*dy);
}

// Position of  line segment connecting  intersection points of circles with 
// distance d between centers.
double intersect_pos(double d, double r1, double r2) {
    return (r1*r1 - r2*r2 + d*d) / (2*d);
}

// Area cut off from circle by chord at position x relative to center.
double slice_area(double x, double r) {
    double y = sqrt(r*r - x*x);
    double alpha = atan(y/x);
    if (alpha < 0)
        alpha = alpha + PI;
    return alpha * r*r - y * x;
}

string read_solve_case() {
    int N, M;
    cin >> N >> M;
    vector<pair<double, double>> P(N);
    for (int i = 0; i < N; ++i)
        cin >> P[i].first >> P[i].second;
    ostringstream output;
    output << setprecision(7) << fixed;
    for (int j = 0; j < M; ++j) {
        pair<double, double> q;
        cin >> q.first >> q.second;
        double r0 = dist(P[0], q);
        double r1 = dist(P[1], q);
        cerr << "r0 = " << r0 << "; r1 = " << r1 << endl;
        double centers_dist = dist(P[0], P[1]);
        cerr << "cd = " << centers_dist << endl;
        double x0 = intersect_pos(centers_dist, r0, r1);
        double x1 = centers_dist - x0;
        cerr << "x0 = " << x0 << "; x1 = " << x1 << endl;
        double ar0 = slice_area(x0, r0);
        double ar1 = slice_area(x1, r1);
        cerr << "ar0 = " << ar0 << "; ar1 = " << ar1 << endl;
        output << ar0 + ar1;
        if (j+1 < M)
            output << ' ';
    }
    return output.str();
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
