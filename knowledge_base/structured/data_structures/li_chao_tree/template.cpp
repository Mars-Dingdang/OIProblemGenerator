#include <iostream>
#include <algorithm>
using namespace std;

constexpr int MAXN = 40000;
constexpr double eps = 1e-9;

int cmp(double x, double y) {
  if (x - y > eps) return 1;
  if (y - x > eps) return -1;
  return 0;
}

double calc(int id, int x, vector<pair<double, double>>& lines) {
  if (id == 0) return -1e18;
  return lines[id].first * x + lines[id].second;
}

template<typename T>
pair<double, int> pmax(pair<double, int> a, pair<double, int> b) {
  int cmp_res = cmp(a.first, b.first);
  if (cmp_res == -1) return b;
  if (cmp_res == 1) return a;
  return a.second < b.second ? a : b;
}

struct LiChaoTree {
  int root = 0;
  vector<int> tree;
  vector<pair<double, double>> lines;
  vector<int> ls, rs;
  int idx = 0;
  int n = MAXN;

  LiChaoTree(int maxn) : n(maxn) {
    tree.resize(4 * n + 5, 0);
    ls.resize(4 * n + 5, 0);
    rs.resize(4 * n + 5, 0);
    lines.emplace_back(0.0, 0.0); // dummy line at index 0
  }

  void add_line(double k, double b) {
    lines.emplace_back(k, b);
    int id = lines.size() - 1;
    update(1, 1, n, 1, n, id);
  }

  void upd(int &root, int cl, int cr, int u) {
    if (!root) {
      root = ++idx;
      tree[root] = u;
      return;
    }
    int v = tree[root];
    int mid = (cl + cr) >> 1;
    int bmid = cmp(calc(u, mid), calc(v, mid));
    if (bmid == 1 || (!bmid && u < v)) swap(u, v);
    tree[root] = v;
    int bl = cmp(calc(u, cl), calc(v, cl));
    int br = cmp(calc(u, cr), calc(v, cr));
    if (bl == 1 || (!bl && u < v)) {
      upd(ls[root], cl, mid, u);
    }
    if (br == 1 || (!br && u < v)) {
      upd(rs[root], mid + 1, cr, u);
    }
  }

  void update(int root, int cl, int cr, int l, int r, int u) {
    if (l <= cl && cr <= r) {
      upd(tree[root], cl, cr, u);
      return;
    }
    int mid = (cl + cr) >> 1;
    if (l <= mid) update(root << 1, cl, mid, l, r, u);
    if (mid < r) update(root << 1 | 1, mid + 1, cr, l, r, u);
  }

  pair<double, int> query(int root, int cl, int cr, int pos) {
    if (cr < pos || pos < cl) return {-1e18, 0};
    double res = calc(tree[root], pos);
    if (cl == cr) return {res, tree[root]};
    return pmax({res, tree[root]}, 
                pmax(query(root << 1, cl, mid, pos),
                     query(root << 1 | 1, mid + 1, cr, pos)));
  }
};