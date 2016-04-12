#include <cassert>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;
    
typedef pair<int,int> Coords;

namespace std {
    template<>
    struct hash<Coords> {
        size_t operator()(const Coords &v) const {
            size_t h = hash<int>()(v.first);
            h ^= hash<int>()(v.second) << 1;
            return h;
        }
    };
}

class Bitmap {
    typedef unsigned char Cell;
    vector<Cell> data;
    int R, C;
public:
    Bitmap(): R(0), C(0) { };
    Bitmap(int R, int C): R(R), C(C), data(R*C, 0) { };
    int height() const { return R; };
    int width() const { return C; };
    int get(int y, int x) const { return data[y*C + x]; };
    void set(int y, int x, Cell val) { data[y*C + x] = val; };
    bool in_bounds(int y, int x) { return x >= 0 && x < C && y >= 0 && y < R; }
    void fill(Cell contents);
    int flood_fill(int y, int x, Cell newval);
    void paste_at(Bitmap &src, int y, int x);
    bool flood_divisible_check(int divisor);
    Bitmap rotated_right() const;
    string dump() const;
};

void Bitmap::fill(Cell contents) {
    for (int i = 0; i < R*C; i++) {
        data[i] = contents;
    }
}

int Bitmap::flood_fill(int y, int x, Cell newval) {
    const int steps[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    Cell oldval = get(y, x);
    queue<Coords> frontier;
    frontier.emplace(y, x);
    set(y, x, newval);
    int filled = 1;
    while (!frontier.empty()) {
        Coords next, cur = frontier.front();
        frontier.pop();
        for (int i = 0; i < 4; ++i) {
            next = cur;
            next.first += steps[i][0];
            next.second += steps[i][1];
            if (in_bounds(next.first, next.second) && 
                    get(next.first, next.second) == oldval) {
                filled += 1;
                set(next.first, next.second, newval);
                frontier.push(next);
            }
        }
    }
    return filled;
}

void Bitmap::paste_at(Bitmap &src, int y, int x) {
    assert(src.height() + y <= height());
    assert(src.width() + x <= width());
    for (int i = 0; i < src.height(); ++i) {
        for (int j = 0; j < src.width(); ++j) {
            set(i+y, j+x, src.get(i, j)); 
        }
    }
}

// Check if continguous regions of zeroes are of size divisible by divisor.
// Destructively.
bool Bitmap::flood_divisible_check(int divisor) {
    for (int y = 0; y < height(); ++y) {
        for (int x = 0; x < width(); ++x) {
            if (get(y, x) != 0) {
                continue;
            }
            if (flood_fill(y, x, 1) % divisor != 0) {
                return false;
            }
        }
    }
    return true;
}

Bitmap Bitmap::rotated_right() const {
    Bitmap result(width(), height());
    for (int y = 0; y < height(); ++y) {
        for (int x = 0; x < width(); ++x) {
            result.set(x, height() - 1 - y, get(y, x));
        }
    }
    return result;
}

string Bitmap::dump() const {
    string result(R*(C + 1), '.');
    for (int y = 0; y < R; ++y) {
        for (int x = 0; x < C; ++x) {
            if (get(y, x) != 0) {
                result[y*(C+1) + x] = '#';
            }
        }
        result[y*(C+1) + C] = '\n';
    }
    return result;
}

class OminoGenerator {
    struct choice_node { 
        unordered_set<Coords> filled_cells;
        vector<Coords> neighbor_cells;
        int current_choice;
        choice_node(Bitmap &bitmap);
        choice_node(const choice_node &parent, Bitmap &bitmap);
    };
    bool _finished;
    int size, h, w;
    stack<choice_node> state;
    Bitmap reference_bitmap;
    Bitmap current_omino;
    void reinit_choices();
public:
    OminoGenerator(int X, int R, int C);
    void next();
    Bitmap current() const { return current_omino; };
    bool finished() const { return _finished; };
};

OminoGenerator::choice_node::choice_node(Bitmap &bitmap) { 
    filled_cells.emplace(0, 0);
    if (bitmap.in_bounds(0, 1)) {
        neighbor_cells.emplace_back(0,1);
    }
    if (bitmap.in_bounds(1, 0)) {
        neighbor_cells.emplace_back(1,0);
    }
    current_choice = 0;
};

OminoGenerator::choice_node::choice_node(const choice_node &parent,
        Bitmap &bitmap) {
    const int steps[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    filled_cells = parent.filled_cells;
    Coords added = parent.neighbor_cells[parent.current_choice];
    filled_cells.insert(added);
    current_choice = 0;
    unordered_set<Coords> seen_neighbors;
    for (auto icell = filled_cells.begin(); icell != filled_cells.end(); 
            ++icell) {
        Coords neighbor; 
        for (int i = 0; i < 4; ++i) {
            neighbor.first = icell->first + steps[i][0];
            neighbor.second = icell->second + steps[i][1];
        
            if (!bitmap.in_bounds(neighbor.first, neighbor.second) ||
                    seen_neighbors.count(neighbor) || 
                    filled_cells.count(neighbor)) {
                continue;
            }
            neighbor_cells.push_back(neighbor);
            seen_neighbors.insert(neighbor);
        }
    }
}

void OminoGenerator::reinit_choices() {
    while (state.size() < size) {
        state.emplace(state.top(), reference_bitmap);
    }
    int maxx = 0;
    int maxy = 0;
    unordered_set<Coords> &cells = state.top().filled_cells;
    for (auto &cell : cells) {
        maxy = max(maxy, cell.first); 
        maxx = max(maxx, cell.second); 
    }
    current_omino = Bitmap(maxy+1, maxx+1);
    for (auto &cell : cells) {
        current_omino.set(cell.first, cell.second, 1);
    }
}

OminoGenerator::OminoGenerator(int X, int R, int C): size(X), h(R), w(C), 
_finished(false), reference_bitmap(R, C) {
    state.emplace(reference_bitmap);
    reinit_choices();
}

void OminoGenerator::next() {
    do  {
        state.pop(); 
    } while (!state.empty() && 
            state.top().current_choice+1 >= state.top().neighbor_cells.size());
    if (state.empty()) {
        _finished = true;
        return;
    }
    state.top().current_choice += 1;
    reinit_choices();
}

bool richard_wins(int X, int R, int C) {
    if (R*C % X != 0) {
        return true;
    }
    // Can surround a single space with an omino
    if (X >= 7) {
        return true;
    }
    if (X > max(R, C) || X > 2*min(R, C)) {
        return true;
    }
    Bitmap grid(R, C);
    for (OminoGenerator gen(X, R, C); !gen.finished(); gen.next()) {
        bool fitted = false;
        Bitmap omino = gen.current();
        for (int rotations = 1; rotations <= 2 && !fitted; ++rotations) {
            omino = omino.rotated_right();
            for (int y = 0; y <= R - omino.height() && !fitted; ++y) {
                for (int x = 0; x <= C - omino.width() && !fitted; ++x) {
                    grid.fill(0);
                    grid.paste_at(omino, y, x);
                    if (grid.flood_divisible_check(X)) {
                        fitted = true;
                    }
                }
            }
        }
        if (!fitted) {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int ci = 1; ci <= T; ++ci) {
        int X, R, C;
        cin >> X >> R >> C;
        cout << "Case #" << ci << ": ";
        cout << (richard_wins(X, R, C) ? "RICHARD" : "GABRIEL") << endl;
    }
    return 0;
}

