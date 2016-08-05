#include <everything.h>

using namespace std;

const i64 MODULUS = 1'000'000'007;

i64 modular_inverse(i64 n1, i64 n2) {
    i64 saved_n1 = n1;
    i64 k1 = 1, l1 = 0;
    i64 k2 = 0, l2 = 1;
    while (n1 != 1) {
        i64 div = n1 / n2;
        i64 mod = n1 % n2;
        tie(n1, k1, l1, n2, k2, l2) = 
            make_tuple(n2, k2, l2, mod, k1 - div * k2, l1 - div * l2);
    }
    return (l1 >= 0 ? l1 : (l1 + saved_n1)) % saved_n1;
}

class FactCache {
    vector<u32> data;
public:
    FactCache(u32 max_arg);
    i64 operator()(u32 n) const { return data[n]; }
};

FactCache::FactCache(u32 max_arg): data(max_arg+1) {
    i64 val = data.at(0) = 1;
    for (u32 i = 1; i <= max_arg; ++i) {
        val = (val * i) % MODULUS;
        data.at(i) = val;
    }
}

FactCache factorial(100);

class CombCache {
    vector<vector<u32>> data;
public:
    CombCache(u32 max_args);
    i64 operator()(u32 n, u32 k) const { return data[n][k]; }
};

CombCache::CombCache(u32 max_args): data(max_args+1) {
    for (u32 n = 0; n <= max_args; ++n) {
        data.at(n).resize(max_args+1);
        for (u32 k = 0; k <= n; ++k) {
            i64 numerator = factorial(n);
            i64 denominator = factorial(n-k) * factorial(k) % MODULUS;
            i64 den_inv = modular_inverse(MODULUS, denominator);
            data.at(n).at(k) = numerator * den_inv % MODULUS;
        }
    }
}

CombCache num_choices(100);

struct TrieNode {
    unordered_map<char, unique_ptr<TrieNode>> children;
    bool end_of_word = false;
    u32 num_words = 0;
};

i64 count_max_nodes(TrieNode &node, u32 num_servers) {
    i64 max_nodes = min(node.num_words, num_servers);
    for (auto& c_pn : node.children) {
        max_nodes += count_max_nodes(*c_pn.second, num_servers); }
    return max_nodes;
}

i64 free_spread(TrieNode &node, u32 num_servers);

i64 count_ways(TrieNode &node, u32 num_servers) {
    if (node.num_words <= num_servers) {
        return free_spread(node, num_servers);
    }
    auto child_lt = [](auto& c_pn1, auto& c_pn2) {
        return c_pn1.second->num_words < c_pn2.second->num_words;
    };
    u32 max_child_size = 
        max_element(node.children.begin(), 
                    node.children.end(), child_lt)->second->num_words;
    if (max_child_size >= num_servers) {
        i64 num_ways = node.end_of_word ? num_servers : 1;
        for (auto& c_pn : node.children) {
            num_ways *= count_ways(*c_pn.second, num_servers); 
            num_ways %= MODULUS;
        }
        return num_ways;
    } 

    i64 num_spreads = node.end_of_word ? num_servers : 1;
    for (auto& c_pn : node.children) {
        num_spreads *= num_choices(num_servers, c_pn.second->num_words); 
        num_spreads %= MODULUS;
    }
    u32 max_empty = num_servers - max_child_size;
    for (u32 num_empty = 1; num_empty <= max_empty; ++num_empty) {
        u32 filled_servers = num_servers - num_empty;
        i64 bad_spreads = node.end_of_word ? filled_servers : 1;
        bad_spreads *= num_choices(num_servers, filled_servers);
        for (auto& c_pn : node.children) {
            bad_spreads *= num_choices(filled_servers, c_pn.second->num_words);
            bad_spreads %= MODULUS;
        }
        num_spreads += MODULUS - bad_spreads * (num_empty % 2 ? 1 : -1);
        num_spreads %= MODULUS;
    }
    i64 num_ways = num_spreads;
    for (auto& c_pn : node.children) {
        num_ways *= count_ways(*c_pn.second, c_pn.second->num_words);
        num_ways %= MODULUS;
    }
    return num_ways;
}

i64 free_spread(TrieNode &node, u32 num_servers) {
    i64 num_ways = num_choices(num_servers, node.num_words);
    num_servers = node.num_words;
    if (node.end_of_word) {
        num_ways *= num_servers--; }
    for (auto& c_pn : node.children) {
        num_ways *= num_choices(num_servers, c_pn.second->num_words);
        num_ways %= MODULUS;
        num_ways *= count_ways(*c_pn.second, c_pn.second->num_words);
        num_ways %= MODULUS;
        num_servers -= c_pn.second->num_words;
    }
    return num_ways;
} 

string read_solve_case() {
    u32 M, N;
    cin >> M >> N;
    TrieNode root;
    for (u32 m = 0; m < M; ++m) {
        string word;
        cin >> word;
        TrieNode *node = &root;
        node->num_words += 1;
        for (char c : word) {
            if (!node->children[c]) {
                node->children[c] = make_unique<TrieNode>(); }
            node = node->children[c].get();
            node->num_words += 1;
        }
        node->end_of_word = true;
    }
    i64 max_nodes = count_max_nodes(root, N);
    i64 num_ways = count_ways(root, N);
    ostringstream ostr;
    ostr << max_nodes << ' ' << num_ways;
    return ostr.str();
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
