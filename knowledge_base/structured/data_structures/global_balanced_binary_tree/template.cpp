#include <vector>
#include <cstdio>

const int MAXN = 100005;

std::vector<int> G[MAXN];
int n, fa[MAXN], son[MAXN], sz[MAXN];
int b[MAXN], bs[MAXN], l[MAXN], r[MAXN], f[MAXN], ss[MAXN];
int a[MAXN], s[MAXN]; // lazy tag and subtree sum

void dfsS(int u) {
  sz[u] = 1;
  for (int v : G[u]) {
    dfsS(v);
    sz[u] += sz[v];
    if (sz[v] > sz[son[u]]) son[u] = v;
  }
}

int cbuild(int bl, int br) {
  int x = bl, y = br;
  while (y - x > 1) {
    int mid = (x + y) >> 1;
    if (2 * (bs[mid] - bs[bl]) <= bs[br] - bs[bl])
      x = mid;
    else
      y = mid;
  }
  int root = b[x];
  ss[root] = br - bl;
  if (bl < x) {
    l[root] = cbuild(bl, x);
    f[l[root]] = root;
  }
  if (x + 1 < br) {
    r[root] = cbuild(x + 1, br);
    f[r[root]] = root;
  }
  return root;
}

int build(int x) {
  int y = x;
  do {
    for (int v : G[y])
      if (v != son[y])
        f[build(v)] = y;
  } while (y = son[y]);

  y = 0;
  do {
    b[y++] = x;
    bs[y] = bs[y - 1] + sz[x] - sz[son[x]];
  } while (x = son[x]);

  return cbuild(0, y);
}

void add(int x) {
  bool t = true;
  int z = 0;
  while (x) {
    s[x] += z;
    if (t) {
      a[x]++;
      if (r[x]) a[r[x]]--;
      z += 1 + ss[l[x]];
      s[x] -= ss[r[x]];
    }
    t = (x != l[f[x]]);
    if (t && x != r[f[x]]) z = 0;
    x = f[x];
  }
}

int query(int x) {
  int ret = 0;
  bool t = true;
  int z = 0;
  while (x) {
    if (t) {
      ret += s[x] - s[r[x]];
      ret -= 1LL * ss[r[x]] * a[r[x]];
      z += 1 + ss[l[x]];
    }
    ret += 1LL * z * a[x];
    t = (x != l[f[x]]);
    if (t && x != r[f[x]]) z = 0;
    x = f[x];
  }
  return ret;
}