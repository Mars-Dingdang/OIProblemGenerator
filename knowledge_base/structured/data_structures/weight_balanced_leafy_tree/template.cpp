#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

const double ALPHA = 0.25; // Recommended α = 1/4
const int MAX_NODES = 200000;

int ch[MAX_NODES][2], sz[MAX_NODES], val[MAX_NODES];
int id = 0, pool[MAX_NODES], top = 0;

void push_up(int x) {
    sz[x] = sz[ch[x][0]] + sz[ch[x][1]];
    val[x] = val[ch[x][1]]; // Example: max value from right child (can be customized)
}

int new_node() {
    int x = top ? pool[--top] : ++id;
    ch[x][0] = ch[x][1] = sz[x] = val[x] = 0;
    return x;
}

void del_node(int& x) {
    pool[top++] = x;
    x = 0;
}

int new_leaf(int v) {
    int x = new_node();
    val[x] = v;
    sz[x] = 1;
    return x;
}

int join(int x, int y) {
    if (!x || !y) return x | y;
    int z = new_node();
    ch[z][0] = x;
    ch[z][1] = y;
    push_up(z);
    return z;
}

std::pair<int, int> cut(int& x) {
    int l = ch[x][0], r = ch[x][1];
    del_node(x);
    return {l, r};
}

bool too_heavy(int sx, int sy) {
    return sy < ALPHA * (sx + sy);
}

bool need_double_rotation(int x, bool r) {
    return sz[ch[x][!r]] > sz[x] / (2 - ALPHA);
}

void rotate(int& x, bool r) {
    int y = ch[x][r];
    ch[x][r] = ch[y][!r];
    ch[y][!r] = x;
    push_up(x);
    push_up(y);
    x = y;
}

void balance(int& x) {
    if (sz[x] == 1) return;
    bool r = sz[ch[x][1]] > sz[ch[x][0]];
    if (!too_heavy(sz[ch[x][r]], sz[ch[x][!r]])) return;
    if (need_double_rotation(ch[x][r], r)) {
        rotate(ch[x][r], !r);
    }
    rotate(x, r);
}

int merge(int x, int y) {
    if (!x || !y) return x | y;
    if (too_heavy(sz[x], sz[y])) {
        int a, b;
        std::tie(a, b) = cut(x);
        if (too_heavy(sz[b] + sz[y], sz[a])) {
            int c, d;
            std::tie(c, d) = cut(b);
            return merge(merge(a, c), merge(d, y));
        } else {
            return merge(a, merge(b, y));
        }
    } else if (too_heavy(sz[y], sz[x])) {
        int a, b;
        std::tie(a, b) = cut(y);
        if (too_heavy(sz[a] + sz[x], sz[b])) {
            int c, d;
            std::tie(c, d) = cut(a);
            return merge(merge(x, c), merge(d, b));
        } else {
            return merge(merge(x, a), b);
        }
    } else {
        return join(x, y);
    }
}

// Optional: Rebalance by merging children
void rebalance(int& x) {
    if (sz[x] == 1) return;
    if (too_heavy(sz[ch[x][0]], sz[ch[x][1]]) ||
        too_heavy(sz[ch[x][1]], sz[ch[x][0]])) {
        int a, b;
        std::tie(a, b) = cut(x);
        x = merge(a, b);
    }
}