#include <iostream>
#include <vector>
using namespace std;

constexpr int MAXN = 300005;

int T[MAXN][3], f[MAXN], val[MAXN], sum[MAXN], lazy[MAXN], rev[MAXN], top, st[MAXN], tot;
#define ls(x) T[x][0]
#define rs(x) T[x][1]
#define ms(x) T[x][2]

bool isr(int x) { return !x || (rs(f[x]) != x && ls(f[x]) != x); }

bool dir(int x) { return rs(f[x]) == x; }

void pushup(int x) {
    if (!x) return;
    sum[x] = val[x];
    if (ls(x)) sum[x] ^= sum[ls(x)];
    if (rs(x)) sum[x] ^= sum[rs(x)];
    if (ms(x)) sum[x] ^= sum[ms(x)];
}

void pushdown(int x) {
    if (!x || !rev[x]) return;
    swap(ls(x), rs(x));
    if (ls(x)) rev[ls(x)] ^= 1;
    if (rs(x)) rev[rs(x)] ^= 1;
    rev[x] = 0;
}

void upd(int x) {
    if (!isr(x)) upd(f[x]);
    pushdown(x);
}

void rotate(int x) {
    int y = f[x], z = f[y], d = dir(x), w = T[x][d ^ 1];
    if (z) T[z][ms(z) == y ? 2 : dir(y)] = x;
    T[x][d ^ 1] = y;
    T[y][d] = w;
    if (w) f[w] = y;
    f[y] = x;
    f[x] = z;
    pushup(y);
    pushup(x);
}

void splay(int x) {
    upd(x);
    for (int y; y = f[x], !isr(x); rotate(x))
        if (!isr(y))
            rotate(dir(x) ^ dir(y) ? x : y);
}

int new_node() {
    if (top) return st[top--];
    return ++tot;
}

void setfather(int x, int fa, int type) {
    if (x) f[x] = fa;
    T[fa][type] = x;
}

void del(int x) {
    setfather(ms(x), f[x], 1);
    if (ls(x)) {
        int p = ls(x);
        pushdown(p);
        while (rs(p)) p = rs(p), pushdown(p);
        splay(p);
        setfather(rs(x), p, 1);
        setfather(p, f[x], 2);
        pushup(p);
        pushup(f[x]);
    } else {
        setfather(rs(x), f[x], 2);
    }
    // Clear node
    ls(x) = rs(x) = ms(x) = val[x] = sum[x] = rev[x] = 0;
    st[++top] = x;
}

void splice(int x) {
    splay(x);
    int y = f[x];
    splay(y);
    pushdown(x);
    if (rs(y)) {
        swap(f[ms(x)], f[rs(y)]);
        swap(ms(x), rs(y));
    } else {
        del(x);
    }
    pushup(x);
    pushup(y);
}

void access(int x) {
    splay(x);
    if (rs(x)) {
        int y = new_node();
        setfather(ms(x), y, 0);
        setfather(rs(x), y, 2);
        rs(x) = 0;
        setfather(y, x, 2);
        pushup(y);
        pushup(x);
    }
    while (f[x]) {
        splice(f[x]);
        x = f[x];
        pushup(x);
    }
    splay(x);
}

void makeroot(int x) {
    access(x);
    rev[x] ^= 1;
    pushdown(x);
}

void split(int x, int y) {
    makeroot(x);
    access(y);
}

void link(int x, int y) {
    makeroot(x);
    access(y);
    setfather(x, y, 1);
    pushup(y);
}

void cut(int x, int y) {
    split(x, y);
    setfather(x, 0, 1);
    pushup(y);
}

int query_path(int x, int y) {
    split(x, y);
    return sum[y];
}

void update_node(int x, int v) {
    access(x);
    val[x] = v;
    pushup(x);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
        sum[i] = val[i];
    }
    while (m--) {
        int op, x, y; cin >> op >> x;
        if (op == 0) {
            cin >> y;
            cout << query_path(x, y) << '\n';
        } else if (op == 1) {
            cin >> y;
            link(x, y);
        } else if (op == 2) {
            cin >> y;
            cut(x, y);
        } else {
            update_node(x, y);
        }
    }
    return 0;
}