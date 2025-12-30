#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#define LC o << 1
#define RC o << 1 | 1
using namespace std;
constexpr int MAXN = 1000010;

int n, m, a[MAXN], u[MAXN], x[MAXN], l[MAXN], r[MAXN], k[MAXN], cur, cur1, cur2, q1[MAXN], q2[MAXN], v[MAXN];
char op[MAXN];
set<int> ST;
map<int, int> mp;

struct segment_tree {
  int cur, rt[MAXN * 4], sum[MAXN * 60], lc[MAXN * 60], rc[MAXN * 60];

  void build(int& o) { o = ++cur; }

  void print(int o, int l, int r) {
    if (!o) return;
    if (l == r && sum[o]) printf("%d ", l);
    int mid = (l + r) >> 1;
    print(lc[o], l, mid);
    print(rc[o], mid + 1, r);
  }

  void update(int& o, int l, int r, int x, int v) {
    if (!o) o = ++cur;
    sum[o] += v;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid)
      update(lc[o], l, mid, x, v);
    else
      update(rc[o], mid + 1, r, x, v);
  }
} st;

namespace fenwick_impl {
  int lowbit(int o) { return o & (-o); }

  void upd(int o, int x, int v) {
    for (; o <= n; o += lowbit(o)) st.update(st.rt[o], 1, n, x, v);
  }

  void gtv(int o, int* A, int& p) {
    p = 0;
    for (; o; o -= lowbit(o)) A[++p] = st.rt[o];
  }

  int qry(int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1, siz = 0;
    for (int i = 1; i <= cur1; i++) siz += st.sum[st.lc[q1[i]]];
    for (int i = 1; i <= cur2; i++) siz -= st.sum[st.lc[q2[i]]];
    if (siz >= k) {
      for (int i = 1; i <= cur1; i++) q1[i] = st.lc[q1[i]];
      for (int i = 1; i <= cur2; i++) q2[i] = st.lc[q2[i]];
      return qry(l, mid, k);
    } else {
      for (int i = 1; i <= cur1; i++) q1[i] = st.rc[q1[i]];
      for (int i = 1; i <= cur2; i++) q2[i] = st.rc[q2[i]];
      return qry(mid + 1, r, k - siz);
    }
  }
}

using namespace fenwick_impl;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", a + i), ST.insert(a[i]);
  for (int i = 1; i <= m; i++) {
    scanf(" %c", op + i);
    if (op[i] == 'C')
      scanf("%d%d", u + i, x + i), ST.insert(x[i]);
    else
      scanf("%d%d%d", l + i, r + i, k + i);
  }
  int cnt = 0;
  for (set<int>::iterator it = ST.begin(); it != ST.end(); it++)
    mp[*it] = ++cnt, v[cnt] = *it;
  for (int i = 1; i <= n; i++) upd(i, mp[a[i]], 1);
  for (int i = 1; i <= m; i++) {
    if (op[i] == 'C') {
      upd(u[i], mp[a[u[i]]], -1);
      a[u[i]] = x[i];
      upd(u[i], mp[a[u[i]]], 1);
    } else {
      cur1 = 0; gtv(r[i], q1, cur1);
      cur2 = 0; gtv(l[i] - 1, q2, cur2);
      printf("%d\n", v[qry(1, n, k[i])]);
    }
  }
  return 0;
}