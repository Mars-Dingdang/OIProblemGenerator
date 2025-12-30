#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;

struct LCT {
    int ch[MAXN][2], fa[MAXN];
    long long val[MAXN], sum[MAXN], add[MAXN], mul[MAXN];
    int rev[MAXN], siz[MAXN];

    void clear(int x) {
        ch[x][0] = ch[x][1] = fa[x] = 0;
        val[x] = sum[x] = add[x] = 0;
        rev[x] = 0; mul[x] = 1;
        siz[x] = 1;
    }

    bool isroot(int x) {
        return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
    }

    int getch(int x) {
        return ch[fa[x]][1] == x;
    }

    void maintain(int x) {
        siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1;
        sum[x] = (sum[ch[x][0]] + sum[ch[x][1]] + val[x]);
    }

    void pushdown(int x) {
        if (rev[x]) {
            if (ch[x][0]) {
                swap(ch[ch[x][0]][0], ch[ch[x][0]][1]);
                rev[ch[x][0]] ^= 1;
            }
            if (ch[x][1]) {
                swap(ch[ch[x][1]][0], ch[ch[x][1]][1]);
                rev[ch[x][1]] ^= 1;
            }
            rev[x] = 0;
        }
        if (mul[x] != 1) {
            if (ch[x][0]) {
                mul[ch[x][0]] = (mul[ch[x][0]] * mul[x]);
                val[ch[x][0]] = (val[ch[x][0]] * mul[x]);
                sum[ch[x][0]] = (sum[ch[x][0]] * mul[x]);
                add[ch[x][0]] = (add[ch[x][0]] * mul[x]);
            }
            if (ch[x][1]) {
                mul[ch[x][1]] = (mul[ch[x][1]] * mul[x]);
                val[ch[x][1]] = (val[ch[x][1]] * mul[x]);
                sum[ch[x][1]] = (sum[ch[x][1]] * mul[x]);
                add[ch[x][1]] = (add[ch[x][1]] * mul[x]);
            }
            mul[x] = 1;
        }
        if (add[x]) {
            if (ch[x][0]) {
                add[ch[x][0]] += add[x];
                val[ch[x][0]] += add[x];
                sum[ch[x][0]] += add[x] * siz[ch[x][0]];
            }
            if (ch[x][1]) {
                add[ch[x][1]] += add[x];
                val[ch[x][1]] += add[x];
                sum[ch[x][1]] += add[x] * siz[ch[x][1]];
            }
            add[x] = 0;
        }
    }

    void update(int x) {
        if (!isroot(x)) update(fa[x]);
        pushdown(x);
    }

    void rotate(int x) {
        int y = fa[x], z = fa[y], k = getch(x), w = ch[x][!k];
        if (!isroot(y)) ch[z][getch(y)] = x;
        ch[x][!k] = y;
        ch[y][k] = w;
        if (w) fa[w] = y;
        fa[y] = x;
        fa[x] = z;
        maintain(y);
        maintain(x);
    }

    void splay(int x) {
        update(x);
        for (int f = fa[x]; !isroot(x); rotate(x), f = fa[x]) {
            if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
        }
    }

    void access(int x) {
        for (int y = 0; x; y = x, x = fa[x]) {
            splay(x);
            ch[x][1] = y;
            maintain(x);
        }
    }

    void makeroot(int x) {
        access(x);
        splay(x);
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
    }

    void split(int x, int y) {
        makeroot(x);
        access(y);
        splay(y);
    }

    void link(int x, int y) {
        makeroot(x);
        fa[x] = y;
    }

    void cut(int x, int y) {
        split(x, y);
        if (ch[y][0] == x) ch[y][0] = fa[x] = 0;
        maintain(y);
    }

    int findroot(int x) {
        access(x);
        splay(x);
        while (ch[x][0]) {
            pushdown(x);
            x = ch[x][0];
        }
        splay(x);
        return x;
    }
};