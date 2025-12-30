#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
const int MAXK = 2e5 + 5;

struct Element {
    int a, b, c;
    int cnt; // multiplicity of identical elements
    int res; // number of points that dominate this one
    bool operator!=(const Element& other) const {
        return a != other.a || b != other.b || c != other.c;
    }
} e[MAXN], ue[MAXN];

int n, k, m;
int ans[MAXN];

struct BIT {
    int tree[MAXK];
    int lowbit(int x) { return x & -x; }
    void add(int pos, int val) {
        while (pos <= k) {
            tree[pos] += val;
            pos += lowbit(pos);
        }
    }
    int query(int pos) {
        int res = 0;
        while (pos) {
            res += tree[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
} bit;

bool cmpA(const Element& x, const Element& y) {
    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}

bool cmpB(const Element& x, const Element& y) {
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}

void cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);
    sort(ue + l, ue + mid + 1, cmpB);
    sort(ue + mid + 1, ue + r + 1, cmpB);
    int i = l;
    for (int j = mid + 1; j <= r; ++j) {
        while (i <= mid && ue[i].b <= ue[j].b) {
            bit.add(ue[i].c, ue[i].cnt);
            ++i;
        }
        ue[j].res += bit.query(ue[j].c);
    }
    for (int j = l; j < i; ++j) {
        bit.add(ue[j].c, -ue[j].cnt);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> e[i].a >> e[i].b >> e[i].c;
    }
    sort(e + 1, e + n + 1, cmpA);
    int t = 0;
    for (int i = 1; i <= n; ++i) {
        ++t;
        if (e[i] != e[i + 1]) {
            ++m;
            ue[m] = e[i];
            ue[m].cnt = t;
            ue[m].res = 0;
            t = 0;
        }
    }
    cdq(1, m);
    for (int i = 1; i <= m; ++i) {
        ans[ue[i].res + ue[i].cnt - 1] += ue[i].cnt;
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << '\n';
    }
    return 0;
}