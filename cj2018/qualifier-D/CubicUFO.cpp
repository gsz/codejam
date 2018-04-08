#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

struct Point {
    double x, y, z;
};

vector <Point> facepoints = {{0.5, 0.0, 0.0}, {0.0, 0.5, 0.0},
                             {0.0, 0.0, 0.5}};

Point rotate_zy(Point p, double theta) {
    return Point{p.x, p.y * cos(theta) + p.z * sin(theta),
                 p.z * cos(theta) - p.y * sin(theta)};
}

Point rotate_xy(Point p, double theta) {
    return Point{p.x * cos(theta) - p.y * sin(theta),
                 p.y * cos(theta) + p.x * sin(theta), p.z};
}

using Realfun = double (double);

double binsearch_theta(double lo, double hi, double target, Realfun fun) {
    u32 rounds = 0;
    double mid;
    while (rounds++ < 1000) {
        mid = (lo + hi) / 2;
        double midval = fun(mid);
        if (abs(target - midval) < 1e-14) {
            break;
        }
        else if (target > midval) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return mid;
}

const double pi = acos(-1);

void read_solve_print_case() {
    double A;
    cin >> A;
    vector<Point> resultpoints;
    if (A < sqrt(2)) {
        double theta = binsearch_theta(0, pi/4, A,
        [](double theta) { return cos(theta) + sin(theta); });
        for (Point &p : facepoints)
            resultpoints.push_back(rotate_xy(p, theta));
    } else {
        double theta = binsearch_theta(0, atan(1/sqrt(2)), A,
            [](double theta) { return sin(theta) + sqrt(2) * cos(theta); });
        for (Point &p : facepoints) {
            Point rp = rotate_xy(p, pi/4);
            resultpoints.push_back(rotate_zy(rp, theta));
        }
    }
    for (Point &p : resultpoints) {
        cout << p.x << ' ' << p.y << ' ' << p.z << endl;
    }
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    cout << setprecision(12) << fixed;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << endl;
        read_solve_print_case();
    }
    return 0;
}
