#include <cmath>
#include <iostream>

constexpr int N = 2e6;
constexpr double ALPHA = 0.7;
int id, rt, lc[N], rc[N], tot[N], tot_active;
int tmp[N], n_tmp;
int val[N], cnt[N], sz[N];

void push_up(int x) {
  tot[x] = 1 + tot[lc[x]] + tot[rc[x]];
  sz[x] = cnt[x] + sz[lc[x]] + sz[rc[x]];
}

void flatten(int x) {
  if (!x) return;
  flatten(lc[x]);
  if (cnt[x]) tmp[n_tmp++] = x;
  flatten(rc[x]);
}

int build(int ll, int rr) {
  if (ll > rr) return 0;
  int mm = (ll + rr) / 2;
  int x = tmp[mm];
  lc[x] = build(ll, mm - 1);
  rc[x] = build(mm + 1, rr);
  push_up(x);
  return x;
}

void rebuild(int& x) {
  n_tmp = 0;
  flatten(x);
  x = build(0, n_tmp - 1);
}

bool insert(int& x, int v, int dep) {
  bool check = false;
  if (!x) {
    x = ++id;
    val[x] = v;
    check = dep > std::log(tot[rt] + 1) / std::log(1 / ALPHA);
  }
  if (val[x] == v) {
    if (!cnt[x]) ++tot_active;
    ++cnt[x];
  } else if (v < val[x]) {
    check = insert(lc[x], v, dep + 1);
  } else {
    check = insert(rc[x], v, dep + 1);
  }
  push_up(x);
  if (check && (tot[lc[x]] > ALPHA * tot[x] || tot[rc[x]] > ALPHA * tot[x])) {
    rebuild(x);
    return false;
  }
  return check;
}

void insert(int v) {
  insert(rt, v, 0);
}

bool remove(int x, int v) {
  if (!x) return false;
  bool succ = true;
  if (v < val[x]) {
    succ = remove(lc[x], v);
  } else if (v > val[x]) {
    succ = remove(rc[x], v);
  } else if (cnt[x]) {
    --cnt[x];
    if (!cnt[x]) --tot_active;
  } else {
    succ = false;
  }
  push_up(x);
  return succ;
}

bool remove(int v) {
  bool succ = remove(rt, v);
  if (!tot_active) {
    rt = 0;
  } else if (succ && tot_active < tot[rt] * ALPHA) {
    rebuild(rt);
  }
  return succ;
}

int find_rank(int v) {
  int res = 0;
  int x = rt;
  while (x && val[x] != v) {
    if (v < val[x]) {
      x = lc[x];
    } else {
      res += sz[lc[x]] + cnt[x];
      x = rc[x];
    }
  }
  return res + sz[lc[x]] + 1;
}

int find_kth(int k) {
  if (k <= 0 || sz[rt] < k) return -1;
  int x = rt;
  for (;;) {
    if (k <= sz[lc[x]]) {
      x = lc[x];
    } else if (k <= sz[lc[x]] + cnt[x]) {
      return val[x];
    } else {
      k -= sz[lc[x]] + cnt[x];
      x = rc[x];
    }
  }
  return -1;
}

int find_prev(int x) {
  return find_kth(find_rank(x) - 1);
}

int find_next(int x) {
  return find_kth(find_rank(x + 1));
}