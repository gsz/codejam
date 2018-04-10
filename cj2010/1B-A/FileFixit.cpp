#include <everything.h>

using namespace std;

struct Dirtree {
    unordered_map<string, unique_ptr<Dirtree>> subdirs;
    u32 mkdir(const string &path, u32 pos);
};

u32 Dirtree::mkdir(const string &path, u32 pos) {
    if (pos >= path.size())
        return 0;
    u32 nextslash = min(path.find('/', pos+1), path.size());
    string dirname = path.substr(pos, nextslash - pos);
    if (subdirs.count(dirname)) {
        return subdirs[dirname]->mkdir(path, nextslash + 1);
    } else {
        subdirs[dirname].reset(new Dirtree);
        return 1 + subdirs[dirname]->mkdir(path, nextslash + 1);
    }
}

int read_solve_case() {
    int N, M;
    cin >> N >> M;
    Dirtree tree;
    for (int i = 0; i < N; ++i) {
        string path;
        cin >> path;
        tree.mkdir(path, 1);
    }
    u32 mkdirs = 0;
    for (int i = 0; i < M; ++i) {
        string path;
        cin >> path;
        mkdirs += tree.mkdir(path, 1);
    }
    return mkdirs;
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
