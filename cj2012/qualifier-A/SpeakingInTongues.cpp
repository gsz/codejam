#include <everything.h>

using namespace std;

const string alphabet    = " abcdefghijklmnopqrstuvwxyz";
const string trans_table = " ynficwlbkuomxsevzpdrjgthaq";

class Decoder {
    unordered_map<char, char> table;
public:
    Decoder() {
        for (u32 i = 0; i < trans_table.size(); ++i) {
            table[trans_table[i]] = alphabet[i]; }
    }
    char operator()(char c) { return table[c]; }
};

Decoder decode;

string read_solve_case() {
    string G;
    getline(cin, G);
    string output;
    for (char c : G) {
        output += decode(c); }
    return output;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << read_solve_case() << endl;
    }
    return 0;
}

