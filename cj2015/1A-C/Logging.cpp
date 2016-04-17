#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

struct Vec2D {
    long long int x, y;
    Vec2D(long long int nx, long long int ny): x(nx), y(ny) { };
    Vec2D operator+(const Vec2D &other) const {
        return Vec2D(x + other.x, y + other.y);
    }
    Vec2D operator-(const Vec2D &other) const {
        return Vec2D(x - other.x, y - other.y);
    }
    Vec2D operator-() const {
        return Vec2D(-x, -y);
    }
    bool operator==(const Vec2D &other) const {
        return x == other.x && y == other.y;
    }
};

bool angle_less(const Vec2D &v1, const Vec2D &v2) {
    int quadrant1 = 2*(v1.y < 0) + ((v1.x < 0) != (v1.y < 0));
    int quadrant2 = 2*(v2.y < 0) + ((v2.x < 0) != (v2.y < 0));
    return quadrant1 < quadrant2 ||
        (quadrant1 == quadrant2 && v1.y * v2.x < v1.x * v2.y);
}

int count_between(const Vec2D &v1, const Vec2D &v2, 
const vector<Vec2D> &sorted_ps) {
    auto ibeg1 = upper_bound(sorted_ps.begin(), sorted_ps.end(), 
                             v1, angle_less);
    auto iend1 = lower_bound(sorted_ps.begin(), sorted_ps.end(), 
                             v2, angle_less);
    auto ibeg2 = upper_bound(sorted_ps.begin(), sorted_ps.end(), 
                             v2, angle_less);
    auto iend2 = lower_bound(sorted_ps.begin(), sorted_ps.end(), 
                             v1, angle_less);
    if (angle_less(v1, v2)) { 
        return min(iend1 - ibeg1, 
                   iend2 - sorted_ps.begin() + sorted_ps.end() - ibeg2);
    }
    return min(iend2 - ibeg2, 
            iend1 - sorted_ps.begin() + sorted_ps.end() - ibeg1);
}

vector<int> solve_case(vector<Vec2D> &input) {
    if (input.size() <= 3) {
        return vector<int>(input.size(), 0);
    }
    vector<Vec2D> ps = input;
    vector<int> result;
    for (auto p0 : input) {
        ps.erase(remove(ps.begin(), ps.end(), p0), ps.end());
        transform(ps.begin(), ps.end(), ps.begin(), 
                [&](auto p) { return p - p0; });
        sort(ps.begin(), ps.end(), angle_less);
        int min_to_remove = input.size();
        for (auto sweep : ps) {
            int to_remove = count_between(sweep, -sweep, ps);
            min_to_remove = min(min_to_remove, to_remove);
        }
        result.push_back(min_to_remove);
        transform(ps.begin(), ps.end(), ps.begin(),
                [&](auto p) { return p + p0; });
        ps.push_back(p0);
    }
    return result;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        int N;
        cin >> N;
        vector<Vec2D> input;
        for (int i = 0; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            input.emplace_back(x, y);
        }
        vector<int> result = solve_case(input);
        cout << "Case #" << ci << ":" << endl;
        for (int i : result) {
            cout << i << endl;
        }
    }
    return 0;
}
