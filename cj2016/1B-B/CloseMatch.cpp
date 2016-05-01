#include <cassert>
#include <memory>
#include <ios>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

// Tries to make C larger than J while minimizing absolute difference.
bool try_fill(string& C, string& J) {
    size_t larger_from = C.size();
    for (size_t i = 0; i < C.size(); ++i) {
        if (C[i] != '?' && J[i] != '?' && C[i] != J[i]) {
            larger_from = i;
            break; 
        }
    }
    if (larger_from < C.size() && C[larger_from] < J[larger_from]) {
        for (int i = larger_from - 1; i >= 0; --i) {
            if (J[i] == '?' && C[i] != '?' && C[i] > '0') {
                J[i] = C[i] - 1;
                larger_from = i;
                break;
            }
            if ((J[i] != '?' && J[i] != '9') || 
                    (C[i] != '?' && C[i] != '0')) {
                break; }
        }
        if (C[larger_from] < J[larger_from]) {
            for (int i = larger_from - 1; i >= 0; --i) {
                if (C[i] == '?' && J[i] == '?') {
                    larger_from = i;
                    C[i] = '1';
                    J[i] = '0';
                    break;
                } else if (C[i] == '?' && J[i] != '9') {
                    larger_from = i;
                    C[i] = J[i] + 1;
                    break;
                } else if (C[i] != '0' && J[i] == '?') {
                    larger_from = i;
                    J[i] = C[i] - 1;
                    break;
                }
            }
        }
        if (C[larger_from] < J[larger_from]) {
            return false; }
    }
    for (size_t i = C.size() - 1; i > larger_from; --i) {
        C[i] = (C[i] == '?' ? '0' : C[i]); 
        J[i] = (J[i] == '?' ? '9' : J[i]);
    }
    for (int i = larger_from - 1; i >= 0; --i) {
        if (C[i] == '?' && J[i] == '?') {
            C[i] = J[i] = '0'; 
        } else if (C[i] == '?') {
            C[i] = J[i];
        } else if (J[i] == '?') {
            J[i] = C[i];
        }
    }
    return true;
}

string read_solve_case() {
    string C1, J1;
    cin >> C1 >> J1;
    string C2 = J1, J2 = C1;
    i64 c1_minus_j1 = -1, c2_minus_j2 = -1;
    if (try_fill(C1, J1)) {
        istringstream sC1(C1), sJ1(J1);
        i64 nC1, nJ1;
        sC1 >> nC1;
        sJ1 >> nJ1;
        c1_minus_j1 = nC1 - nJ1;
        assert(c1_minus_j1 >= 0);
    }
    if (try_fill(C2, J2)) {
        istringstream sC2(C2), sJ2(J2);
        i64 nC2, nJ2;
        sC2 >> nC2;
        sJ2 >> nJ2;
        c2_minus_j2 = nC2 - nJ2;
        assert(c2_minus_j2 >= 0);
    }
    if (c2_minus_j2 == -1) {
        return C1 + ' ' + J1; }
    if (c1_minus_j1 == -1) {
        return J2 + ' ' + C2; }
    if (c1_minus_j1 < c2_minus_j2 ||
            (c1_minus_j1 == c2_minus_j2 && C1 < J2) ||
            (c1_minus_j1 == c2_minus_j2 && C1 == J2 && J1 <= C2)) {
        return C1 + ' ' + J1;
    } else {
        return J2 + ' ' + C2;
    }
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

