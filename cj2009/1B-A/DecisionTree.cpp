#include <everything.h>

using namespace std;

struct DecisionTree {
    double weight;
    string feature;
    shared_ptr<DecisionTree> left, right;

    void read();
    double classify(unordered_set<string> &features, double acc = 1);
};

void DecisionTree::read() {
    char c;
    cin >> ws >> c >> weight >> ws;
    if (cin.peek() != ')') {
        cin >> ws >> feature;
        left = make_shared<DecisionTree>();
        left->read();
        right = make_shared<DecisionTree>();
        right->read();
    }
    cin >> ws >> c;
}

double DecisionTree::classify(unordered_set<string> &features, double acc) {
    if (feature.empty()) {
        return acc * weight;
    } else if (features.count(feature)) {
        return left->classify(features, acc * weight);
    } else {
        return right->classify(features, acc * weight);
    }
}

void read_solve_print_case() {
    int L;
    cin >> L;
    DecisionTree t;
    t.read();
    int A;
    cin >> A;
    for (int i = 0; i < A; ++i) {
        string s;
        int n;
        cin >> s >> n;
        unordered_set<string> feats;
        for (int j = 0; j < n; ++j) {
            cin >> s;
            feats.insert(s);
        }
        cout << t.classify(feats) << endl;
    }
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    cout << setprecision(7) << fixed;
    for (int ci = 1; ci <= T; ++ci) {
        cout << "Case #" << ci << ": " << endl;
        read_solve_print_case();
    }
    return 0;
}
