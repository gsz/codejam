#include <everything.h>

using namespace std;

struct Checker {
    vector<vector<bool>> cache;
    int max_cached;
    
    Checker(int _max_cached); 
    bool is_happy(int n, int base);
};

Checker::Checker(int _max_cached) :
        cache(11, vector<bool>(_max_cached+1)),
        max_cached(_max_cached) 
{
    for (int b = 2; b <= 10; ++b) {
        for (int n = 0; n <= max_cached; ++n) {
            unordered_set<int> seen;
            int m = n;
            seen.insert(m);
            bool happy = true;
            while (m != 1) {
                int newm = 0;
                while (m > 0) {
                    newm += (m % b) * (m % b);
                    m /= b;
                }
                if (seen.count(newm)) {
                    happy = false;
                    break;
                }
                seen.insert(newm);
                m = newm;
            }
            cache[b][n] = happy;
        }
    }
}

bool Checker::is_happy(int n, int base) {
    int newn = 0;
    while (n > 0) {
        newn += (n % base) * (n % base);
        n /= base;
    }
    return cache[base][newn];
}

Checker check(2000);
unordered_map<int, int> memo_answers;

int smallest_allhappy(vector<int> &bases) {
    int bset = 0;
    for (int b : bases)
        bset |= (1 << (b-2));
    if (memo_answers.count(bset))
        return memo_answers[bset];
    bool done = false;
    int n = 1;
    while (!done) {
        n += 1;
        done = true;
        for (int b : bases) {
            if (!check.is_happy(n, b)) {
                done = false;
                break;
            }
        }
    }
    memo_answers[bset] = n;
    return n;
}

int read_solve_case() {
    string inp; 
    getline(cin >> ws, inp);
    istringstream istr(inp);
    vector<int> bases;
    while (!istr.eof()) {
        int b;
        istr >> b;
        bases.push_back(b);
    }
    return smallest_allhappy(bases);
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
