#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

constexpr int N = 100005, M = N / 3 + 10;

int n, m, maxn;
int a[N], ans[M], cnt[N];
bitset<N> sum[M], now;

struct query {
  int l, r, id;
  bool operator<(const query& x) const {
    if (l / maxn != x.l / maxn) return l < x.l;
    return (l / maxn) & 1 ? r < x.r : r > x.r;
  }
} q[M * 3];

void static_set() {
  static int tmp[N];
  memcpy(tmp, a, sizeof(a));
  sort(tmp + 1, tmp + n + 1);
  for (int i = 1; i <= n; i++)
    a[i] = lower_bound(tmp + 1, tmp + n + 1, a[i]) - tmp;
}

void add(int x) {
  now.set(x + cnt[x]);
  cnt[x]++;
}

void del(int x) {
  cnt[x]--;
  now.reset(x + cnt[x]);
}

void solve() {
  int cnt = 0, tot = 0;
  now.reset();
  sort(q + 1, q + m * 3 + 1);
  int L = 1, R = 0;
  for (int i = 1; i <= m * 3; ++i) {
    while (R < q[i].r) add(a[++R]);
    while (L > q[i].l) add(a[--L]);
    while (R > q[i].r) del(a[R--]);
    while (L < q[i].l) del(a[L++]);
    sum[q[i].id] &= now;
  }
  for (int i = 1; i <= m; ++i) {
    printf("%d\n", (int)(3 * (q[3*i-2].r - q[3*i-2].l + 1) - sum[i].count()));
  }
}