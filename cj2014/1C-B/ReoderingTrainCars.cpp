#include <cassert>
#include <limits>
#include <memory>
#include <ios>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <random>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

const u64 MODULUS = 1'000'000'007;

class FactCache {
    vector<u64> data;
public:
    FactCache(u32 maxn);
    u64 operator()(u32 n) const { return data[n]; }
};

FactCache::FactCache(u32 maxn): data(max(maxn+1, 1u)) {
    data[0] = 1;
    for (u32 i = 1; i <= maxn; ++i) {
        data[i] = data[i-1] * i % MODULUS; }
}

FactCache factorial(100);

struct CharInfo {
    bool impure;
    int surrounded, at_front, at_back, pure_strings;
};

struct CaseData {
    int group_num;
    unordered_map<char, char> front_to_back, back_to_front;
    unordered_map<char, CharInfo> cinfo;
};

bool read_case(CaseData& cd) {
    int N;
    cin >> N;
    vector<string> carsets(N);
    for (int i = 0; i < N; ++i) {
        cin >> carsets[i]; }
    for (string carset : carsets) {
        bool seen_change = false;
        char prevc = carset[0];
        for (char c : carset) {
            if (c == prevc) {
                continue; }
            cd.cinfo[prevc].impure = cd.cinfo[c].impure = true;
            if (seen_change) {
                cd.cinfo[prevc].surrounded += 1; }
            seen_change = true;
            prevc = c;
        }
        if (!seen_change) {
            cd.cinfo[carset.front()].pure_strings += 1; 
        } else {
            char groupfront = carset.front(), groupback = carset.back();
            if (groupfront == groupback) {
                return false; }
            cd.cinfo[carset.front()].at_front += 1;
            cd.cinfo[carset.back()].at_back += 1;
            if (cd.back_to_front.count(carset.front())) {
                groupfront = cd.back_to_front[carset.front()];
                cd.back_to_front.erase(carset.front());
                if (groupfront == groupback) {
                    return false; }
            }
            if (cd.front_to_back.count(carset.back())) {
                groupback = cd.front_to_back[carset.back()];
                cd.front_to_back.erase(carset.back());
            }
            cd.front_to_back[groupfront] = groupback;
            cd.back_to_front[groupback] = groupfront;
        }
    }
    return none_of(cd.cinfo.begin(), cd.cinfo.end(), 
            [&](auto& c_cinf) { 
                auto& cinf = c_cinf.second;
                return cinf.at_back > 1 || cinf.at_front > 1 || 
                cinf.surrounded > 1 ||
                (cinf.surrounded && (cinf.pure_strings || 
                                     cinf.at_front || cinf.at_back));
            });
}

u64 read_solve_case() {
    CaseData cd;
    if (!read_case(cd)) {
        return 0; }
    u64 pure_groups = count_if(cd.cinfo.begin(), cd.cinfo.end(),
            [](auto& c_cinf) { return !c_cinf.second.impure; });
    u64 num_orderings = factorial(cd.front_to_back.size() + pure_groups);
    for (auto& c_cinf : cd.cinfo) {
        auto& cinf = c_cinf.second;
        num_orderings = num_orderings * factorial(cinf.pure_strings) % MODULUS;
    }
    return num_orderings;
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
