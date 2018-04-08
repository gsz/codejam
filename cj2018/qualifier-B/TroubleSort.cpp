#include <algorithm>
#include <iostream>
#include <vector>

typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;

using namespace std;

string read_solve_case() {
    u32 N;
    cin >> N;
    vector<u32> even((N+1)/2), odd(N/2);
    for (u32 i = 0; i < N/2; ++i) {
        cin >> even[i] >> odd[i];
    }
    if (N % 2 != 0)
        cin >> even[(N+1)/2 - 1];
    sort(odd.begin(), odd.end());
    sort(even.begin(), even.end());
    vector<u32> arr(N);
    for (u32 i = 0; i < N; ++i)
        arr[i] = (i % 2 == 0 ? even[i/2] : odd[i/2]);
    for (u32 i = 0; i < arr.size()-1; ++i) {
        if (arr[i] > arr[i+1])
            return to_string(i);
    }
    return "OK";
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
