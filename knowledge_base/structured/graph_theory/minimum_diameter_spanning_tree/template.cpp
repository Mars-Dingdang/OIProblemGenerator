#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

constexpr int MAXN = 502;
using ll = long long;
using pii = pair<int, int>;

ll d[MAXN][MAXN], dd[MAXN][MAXN], rk[MAXN][MAXN], val[MAXN];
constexpr ll INF = 1e17;
int n, m;

bool cmp(int a, int b) { return val[a] < val[b]; }

void floyd() {
  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

struct node {
  ll u, v, w;
} a[MAXN * (MAXN - 1) / 2];

void solve() {
  floyd();
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      rk[i][j] = j;
      val[j] = d[i][j];
    }
    sort(rk[i] + 1, rk[i] + 1 + n, cmp);
  }

  ll P = 0, ansP = INF; // 最小直径（点上）
  for (int i = 1; i <= n; i++) {
    if (d[i][rk[i][n]] * 2 < ansP) {
      ansP = d[i][rk[i][n]] * 2;
      P = i;
    }
  }

  ll ansL = INF;
  int f1 = 0, f2 = 0;
  ll disu = 0, disv = 0;

  for (int i = 1; i <= m; i++) {
    ll u = a[i].u, v = a[i].v, w = a[i].w;
    for (int p = n, j = n - 1; j >= 1; j--) {
      if (d[v][rk[u][j]] > d[v][rk[u][p]]) {
        ll temp = d[u][rk[u][j]] + d[v][rk[u][p]] + w;
        if (temp < ansL) {
          ansL = temp;
          f1 = u; f2 = v;
          disu = (temp) / 2 - d[u][rk[u][j]];
          disv = w - disu;
        }
        p = j;
      }
    }
  }

  ll diameter = min(ansP, ansL);
  cout << diameter / 2.0 << '\n';

  vector<pii> edges;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      dd[i][j] = INF;
  for (int i = 1; i <= n; ++i)
    dd[i][i] = 0;

  if (ansP <= ansL) {
    for (int j = 1; j <= n; j++) {
      for (int i = 1; i <= m; ++i) {
        ll u = a[i].u, v = a[i].v, w = a[i].w;
        if (dd[P][u] + w == d[P][v] && dd[P][u] + w < dd[P][v]) {
          dd[P][v] = dd[P][u] + w;
          edges.push_back({u, v});
        }
        u = a[i].v, v = a[i].u, w = a[i].w;
        if (dd[P][u] + w == d[P][v] && dd[P][u] + w < dd[P][v]) {
          dd[P][v] = dd[P][u] + w;
          edges.push_back({u, v});
        }
      }
    }
  } else {
    int new_node = n + 1;
    d[new_node][f1] = disu; d[f1][new_node] = disu;
    d[new_node][f2] = disv; d[f2][new_node] = disv;
    a[m + 1] = {new_node, f1, disu};
    a[m + 2] = {new_node, f2, disv};
    n++;
    m += 2;
    floyd();
    P = new_node;
    for (int j = 1; j <= n; j++) {
      for (int i = 1; i <= m; ++i) {
        ll u = a[i].u, v = a[i].v, w = a[i].w;
        if (dd[P][u] + w == d[P][v] && dd[P][u] + w < dd[P][v]) {
          dd[P][v] = dd[P][u] + w;
          edges.push_back({u, v});
        }
        u = a[i].v, v = a[i].u, w = a[i].w;
        if (dd[P][u] + w == d[P][v] && dd[P][u] + w < dd[P][v]) {
          dd[P][v] = dd[P][u] + w;
          edges.push_back({u, v});
        }
      }
    }
  }

  for (auto [x, y] : edges)
    cout << x << ' ' << y << '\n';
}