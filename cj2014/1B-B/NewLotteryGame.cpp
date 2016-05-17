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

// dynamic table keeps number of combinations that:
// 0 - match parts of A and B seen so far
// 1 - match A, smaller than B
// 2 - match B, smaller tan A
// 3 - smaller than both
void update_dyntable(u64 oldt[4], u64 newt[4], u32 A, u32 B, u32 mask, 
                     u32 bit_A, u32 bit_B) {
    u32 maskbit_A = (A & mask) > 0, maskbit_B = (B & mask) > 0; 
    if (maskbit_A == bit_A && maskbit_B == bit_B) {
        newt[0] += oldt[0]; }
    if (maskbit_A == bit_A) {
        newt[1] += oldt[1];
        if (maskbit_B > bit_B) {
            newt[1] += oldt[0]; }
    }
    if (maskbit_B == bit_B) {
        newt[2] += oldt[2];
        if (maskbit_A > bit_A) {
            newt[2] += oldt[0]; }
    }
    newt[3] += oldt[3];
    if (maskbit_A > bit_A) {
        newt[3] += oldt[1]; }
    if (maskbit_B > bit_B) {
        newt[3] += oldt[2]; }
    if (maskbit_A > bit_A && maskbit_B > bit_B) {
        newt[3] += oldt[0]; }
}

u64 read_solve_case() {
    u32 A, B, K;
    cin >> A >> B >> K;
    vector<int> K_ones;
    for (int bi = 30; bi >= 0; --bi) {
        if (K & (1u << bi)) {
            K_ones.push_back(bi); }
    }
    u64 total_combinations = 0; 
    for (size_t i = 0; i < K_ones.size(); ++i) {
        u32 K_prefix = K & ((1u << 31) - (1u << (K_ones[i] + 1)));
        u64 num_combs1[4] = {1, 0, 0, 0};
        for (int bi = 30; bi >= K_ones[i]; --bi) {
            u64 num_combs2[4] = {0, 0, 0, 0};
            u32 mask = 1u << bi;
            if (K_prefix & mask) {
                update_dyntable(num_combs1, num_combs2, A, B, mask, 1, 1);
            } else {
                update_dyntable(num_combs1, num_combs2, A, B, mask, 0, 0);
                update_dyntable(num_combs1, num_combs2, A, B, mask, 0, 1);
                update_dyntable(num_combs1, num_combs2, A, B, mask, 1, 0);
            }
            copy_n(num_combs2, 4, num_combs1);
        }
        for (int bi = K_ones[i] - 1; bi >= 0; --bi) {
            u64 num_combs2[4] = {0, 0, 0, 0};
            u32 mask = 1u << bi;
            update_dyntable(num_combs1, num_combs2, A, B, mask, 1, 1);
            update_dyntable(num_combs1, num_combs2, A, B, mask, 0, 0);
            update_dyntable(num_combs1, num_combs2, A, B, mask, 0, 1);
            update_dyntable(num_combs1, num_combs2, A, B, mask, 1, 0);
            copy_n(num_combs2, 4, num_combs1);
        }
        total_combinations += num_combs1[3];
    }
    return total_combinations;
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
