#include <iostream>
#include <algorithm>
using namespace std;

const int N = 300010;

struct Node {
    int val, ch[2], d, fa;
    Node() : val(0), ch{0, 0}, d(-1), fa(0) {}
    Node(int v) : val(v), ch{0, 0}, d(0), fa(0) {}
};

Node t[N];

int& rs(int x) {
    return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d];
}

int merge(int x, int y) {
    if (!x || !y) return x | y;
    if (t[x].val > t[y].val) swap(x, y);
    int& rs_ref = rs(x);
    rs_ref = merge(rs_ref, y);
    t[rs_ref].fa = x;
    t[x].d = t[rs(x)].d + 1;
    return x;
}

void erase(int x) {
    t[x].fa = t[x].ch[0] = t[x].ch[1] = 0;
    t[x].d = 0;
}

int find_root(int x) {
    while (t[x].fa) x = t[x].fa;
    return x;
}