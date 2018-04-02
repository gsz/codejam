#include <everything.h>

using namespace std;

void read_solve_print_case() {
    int R, C;
    cin >> R >> C;
    vector<string> pic(R);
    for (int r = 0; r < R; ++r)
        cin >> pic[r];
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (pic[r][c] != '#')
                continue;
            if (r+1 >= R || c+1 >= C 
                    || pic[r][c+1] != '#' || pic[r+1][c] != '#' 
                    || pic[r+1][c+1] != '#') {
                cout << "Impossible" << endl;
                return;
            }
            pic[r][c] = '/';
            pic[r][c+1] = '\\';
            pic[r+1][c] = '\\';
            pic[r+1][c+1] = '/';
        }
    }
    for (string &s : pic)
        cout << s << endl;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << endl;
        read_solve_print_case();
    }
    return 0;
}
