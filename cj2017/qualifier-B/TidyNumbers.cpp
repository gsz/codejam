#include <everything.h>

using namespace std;

u64 read_solve_case() {
    string N;
    cin >> N;
    int blockstart;
    char blockchar = 'z';
    for (u32 i = 0; i < N.size() - 1; ++i) {
        if (N[i] != blockchar) {
            blockstart = i;
            blockchar = N[i];
        }
        if (N[i] > N[i+1]) {
            N[blockstart] -= 1;
            fill(N.begin()+blockstart+1, N.end(), '9');
            break;
        }
    }
    return stoull(N);
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

