#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXQ = 100005;

int n, m, qcnt, rcnt;
long long cur, qsize;
long long a[MAXN], ans[MAXQ], mp[1000005];

struct Query {
    int id, l, r, t;
    bool operator<(const Query& b) const {
        if (l / qsize != b.l / qsize)
            return l / qsize < b.l / qsize;
        if (r / qsize != b.r / qsize)
            return r / qsize < b.r / qsize;
        return t < b.t;
    }
} q[MAXQ];

struct Operation {
    int p, x;
} op[MAXN];

void add(int x) {
    if (!mp[x]) cur++;
    mp[x]++;
}

void del(int x) {
    mp[x]--;
    if (!mp[x]) cur--;
}

void apply(int i, int &L, int &R) {
    if (op[i].p >= L && op[i].p <= R) {
        del(a[op[i].p]);
        add(op[i].x);
    }
    a[op[i].p] = op[i].x;
}

void undo(int i, int &L, int &R) {
    if (op[i].p >= L && op[i].p <= R) {
        del(a[op[i].p]);
        add(op[i].x);
    }
    a[op[i].p] = op[i].x;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    
    while (m--) {
        char type; cin >> type;
        if (type == 'Q') {
            ++qcnt;
            cin >> q[qcnt].l >> q[qcnt].r;
            q[qcnt].id = qcnt;
            q[qcnt].t = rcnt;
        } else {
            ++rcnt;
            cin >> op[rcnt].p >> op[rcnt].x;
        }
    }
    
    qsize = pow(n, 2.0/3);
    sort(q + 1, q + qcnt + 1);
    
    int L = 1, R = 0, T = 0;
    cur = 0;
    
    for (int i = 1; i <= qcnt; ++i) {
        while (T < q[i].t) apply(++T, L, R);
        while (T > q[i].t) undo(T--, L, R);
        while (R < q[i].r) add(a[++R]);
        while (R > q[i].r) del(a[R--]);
        while (L < q[i].l) del(a[L++]);
        while (L > q[i].l) add(a[--L]);
        ans[q[i].id] = cur;
    }
    
    for (int i = 1; i <= qcnt; ++i)
        cout << ans[i] << '\n';
    
    return 0;
}