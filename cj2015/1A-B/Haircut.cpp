#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long int int64;

int64 served_customers_count(int64 time, vector<int> &barber_timings) {
    int64 result = 0;
    for (int bt : barber_timings) {
        result += time / bt;
    }
    return result;
}

int read_solve_case() {
    int B, N;
    cin >> B >> N;
    vector<int> barber_timings;
    for (int bi = 0; bi < B; ++bi) {
        int t;
        cin >> t;
        barber_timings.push_back(t);
    }
    if (N <= B) {
        return N;
    }
    // Binary search over possible time range to find time such that customer
    // N sat down during last customer change.
    int64 range_start = 0, range_end = 100'000L * 100'000'0000L;
    int64 time;
    while (range_start < range_end) {
        time = (range_start + range_end) / 2;
        if (served_customers_count(time, barber_timings) < N - B) {
            range_start = time = time + 1;
        } else {
            range_end = time;
        }
    }
    // If c >= N - B customers are served at that time then (c - (N - B - 1)-th
    // last barber with minimal time spent working on current customer is the 
    // answer.
    int64 customers_served = served_customers_count(time, barber_timings);
    int min_candidate = 100'001, seen_before, answer_candidate;
    for (int bi = barber_timings.size()-1; bi >= 0; --bi) {
        int time_spent = time % barber_timings[bi];
        if (time_spent <= min_candidate) {
            seen_before = time_spent < min_candidate ? 0 : seen_before + 1;
            min_candidate = time_spent;
            if (seen_before == customers_served - (N - B)) {
                answer_candidate = bi;
            }
        }
    }
    return answer_candidate + 1;
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

