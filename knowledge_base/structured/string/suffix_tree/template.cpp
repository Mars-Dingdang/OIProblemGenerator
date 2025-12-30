#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct SuffixTree {
    struct Node {
        int l, r; // edge label s[l..r-1]
        int link;
        map<char, int> next;
        Node(int l = 0, int r = 0) : l(l), r(r), link(0) {}
        int len() const { return r - l; }
    };
    
    string s;
    vector<Node> t;
    int n, pos, node, rem;
    
    SuffixTree(const string &str) : s(str + '$'), n(s.size()), pos(0), node(0), rem(0) {
        t.reserve(2 * n);
        t.emplace_back(); // root = 0
        for (int i = 0; i < n; ++i) extend(i);
    }
    
    void extend(int i) {
        ++rem;
        int last = 0;
        while (rem > 0) {
            if (pos == t[node].len()) {
                pos = 0;
                if (t[node].next.count(s[i])) {
                    node = t[node].next[s[i]];
                    break;
                } else {
                    int leaf = t.size();
                    t.emplace_back(i, n);
                    t[node].next[s[i]] = leaf;
                    if (last) t[last].link = node;
                    last = node;
                }
            } else {
                char edge = s[t[node].l + pos];
                if (edge == s[i]) {
                    ++pos;
                    if (last) t[last].link = node;
                    last = node;
                    break;
                } else {
                    int split = t.size();
                    t.emplace_back(t[node].l, t[node].l + pos);
                    t[node].l += pos;
                    t[split].next[s[t[node].l]] = node;
                    int leaf = t.size();
                    t.emplace_back(i, n);
                    t[split].next[s[i]] = leaf;
                    t[node].link = split;
                    if (last) t[last].link = split;
                    last = split;
                    node = t[t[split].link].next[s[t[split].l]];
                    pos = t[split].len();
                }
            }
            --rem;
            if (node == 0 && pos > 0) {
                --pos;
                node = t[0].next[s[i - rem + 1]];
            } else {
                node = t[node].link ? t[node].link : 0;
            }
        }
    }
    
    // Example: count leaf nodes in subtree (occurrences of suffix)
    int dfs(int u, int &leaves) {
        if (t[u].next.empty()) {
            ++leaves;
            return 1;
        }
        int total = 0;
        for (auto &p : t[u].next) {
            int v = p.second;
            total += dfs(v, leaves);
        }
        // Process internal node: total is number of leaves in subtree
        return total;
    }
};

int main() {
    string s = "ababa";
    SuffixTree st(s);
    int leaves = 0;
    st.dfs(0, leaves);
    cout << "Number of leaves (suffixes): " << leaves << endl;
    return 0;
}