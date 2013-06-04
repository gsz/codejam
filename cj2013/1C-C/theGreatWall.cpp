#include <iostream>
#if defined __GNUC__ || defined __APPLE__
#include <ext/hash_set>
#else
#include <hash_set>
#endif
#include <vector>
#include <algorithm>

#if defined __GNUC__ || defined __APPLE__
namespace std {
    using namespace __gnu_cxx;
};
#endif

struct Attack {
    int d, w, e, s;

    Attack(int d, int w, int e, int s): d(d), w(w), e(e), s(s) { }
};

int attackCmp(const Attack &a1, const Attack &a2) {
    return a1.d < a2.d;
}

struct TreeNode {
    int w, e, mid, minHeight;
    TreeNode *left, *right;

    TreeNode(int w, int e, int mid, TreeNode *left, TreeNode *right,
            int minHeight): w(w), e(e), mid(mid), left(left), right(right)
                            , minHeight(minHeight) {}
};

typedef std::vector<Attack> AttackVec;
AttackVec attacks;
TreeNode *wall;

TreeNode *buildWallTree(std::vector<int>::iterator start, 
        std::vector<int>::iterator end) {
    if (end - start == 1) {
        return new TreeNode(*start, *end, 0, NULL, NULL, 0);
    }
    int w = *start, mid = *(start + (end - start) / 2), e = *end;
    TreeNode *left = buildWallTree(start, start + (end - start) / 2);
    TreeNode *right = buildWallTree(start + (end - start) / 2, end);
    return new TreeNode(w, e, mid, left, right, 0);
}

void destroyWallTree(TreeNode *what = wall) {
    if (!what) {
        return;
    }
    destroyWallTree(what->left);
    destroyWallTree(what->right);
    delete what;
}

bool treeWalk(int w, int e, int s, TreeNode *node, int maxMin, 
        bool build = false) {
    if (w >= e) {
        return false;
    }
    maxMin = std::max(node->minHeight, maxMin);
    if (maxMin >= s) {
        return false;
    }
    if (w == node->w && e == node->e) {
        if (build) {
            node->minHeight = s;
        }
        return true;
    }
    if (build) {
        treeWalk(w, std::min(e, node->mid), s, node->left, maxMin, build);
        treeWalk(std::max(w, node->mid), e, s, node->right, maxMin, build);
        if (node->left->minHeight > node->minHeight &&
                node->right->minHeight > node->minHeight) {
            node->minHeight = std::min(node->left->minHeight,
                    node->right->minHeight);
        }
        return false;
    }
    return (treeWalk(w, std::min(e, node->mid), s, node->left, maxMin)
            || treeWalk(std::max(w, node->mid), e, s, node->right, maxMin));
}

bool checkAttack(Attack &a) {
    return treeWalk(a.w, a.e, a.s, wall, 0);
}

void updateWall(Attack &a) {
    treeWalk(a.w, a.e, a.s, wall, 0, true);
}

void readAttacks() {
    int N;
    int di, ni, wi, ei, si, delta_di, delta_pi, delta_si;
    std::cin >> N;
    attacks.clear();
    for (int ti = 0; ti < N; ti++) {
        std::cin >> di >> ni >> wi >> ei >> si >> delta_di >> delta_pi >> 
            delta_si;
        while (ni-- > 0) {
            attacks.push_back(Attack(di, wi, ei, si));
            di += delta_di;
            wi += delta_pi; ei += delta_pi;
            si += delta_si;
        }
    }
    std::sort(attacks.begin(), attacks.end(), attackCmp);
}

int readSolveCase() {
    readAttacks();
    std::hash_set<int> points;
    for (AttackVec::iterator ai = attacks.begin(); ai < attacks.end(); ai++) {
        points.insert(ai->w);
        points.insert(ai->e);
    }
    std::vector<int> pointVec(points.begin(), points.end());
    std::sort(pointVec.begin(), pointVec.end());
    wall = buildWallTree(pointVec.begin(), pointVec.end());
    AttackVec::iterator ai = attacks.begin();
    int attacksSuccessful = 0;
    AttackVec attacksToday;
    while (ai < attacks.end()) {
        int day = ai->d;
        attacksToday.clear();
        while (ai < attacks.end() && ai->d == day) {
            if (checkAttack(*ai)) {
                attacksSuccessful += 1;
                attacksToday.push_back(*ai);
            }
            ai++;
        }
        for (AttackVec::iterator aj = attacksToday.begin(); 
                aj < attacksToday.end(); aj++) {
            updateWall(*aj);
        }
    }
    destroyWallTree();
    return attacksSuccessful;
}

int main() {
    int T;
    std::cin >> T;
    for (int casenum = 1; casenum <= T; casenum++) {
        std::cout << "Case #" << casenum << ": " << readSolveCase() << 
            std::endl;
    }
}
