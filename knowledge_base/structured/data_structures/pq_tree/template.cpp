#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

const int MAXN = 100001;

class PQTree {
 public:
  PQTree() {}

  void Init(int n) {
    n_ = n, rt_ = tot_ = n + 1;
    for (int i = 1; i <= n; ++i) g_[rt_].emplace_back(i);
  }

  void Insert(const std::string& s) {
    s_ = s;
    Dfs0(rt_);
    Work(rt_);
    while (g_[rt_].size() == 1) rt_ = g_[rt_][0];
    Remove(rt_);
  }

  std::vector<int> ans() {
    DfsAns(rt_);
    return ans_;
  }

  ~PQTree() {}

 private:
  int n_, rt_, tot_, pool_[MAXN], top_ = 0;
  int typ_[MAXN];        // 0: P-node, 1: Q-node
  int col_[MAXN];        // 0: black, 1: white, 2: grey
  std::vector<int> g_[MAXN], ans_;
  std::string s_;

  void Fail() {
    printf("NO\n");
    std::exit(0);
  }

  int NewNode(int ty) {
    int x = top_ ? pool_[top_--] : ++tot_;
    typ_[x] = ty;
    return x;
  }

  void Delete(int u) {
    g_[u].clear();
    pool_[++top_] = u;
  }

  void Dfs0(int u) {
    if (u >= 1 && u <= n_) {
      col_[u] = s_[u] == '1';
      return;
    }
    bool has_white = false, has_black = false;
    for (int v : g_[u]) {
      Dfs0(v);
      if (col_[v] == 1) has_white = true;
      if (col_[v] == 0) has_black = true;
    }
    if (has_black && !has_white) col_[u] = 0;
    else if (!has_black && has_white) col_[u] = 1;
    else col_[u] = 2;
  }

  bool Check(const std::vector<int>& v) {
    int p2 = -1;
    for (int i = 0; i < (int)v.size(); ++i) {
      if (col_[v[i]] == 2) {
        if (p2 != -1) return false;
        p2 = i;
      }
    }
    if (p2 == -1) {
      for (int i = 0; i < (int)v.size(); ++i) {
        if (col_[v[i]] == 1) {
          p2 = i;
          break;
        }
      }
    }
    for (int i = 0; i < p2; ++i)
      if (col_[v[i]] == 1) return false;
    for (int i = p2 + 1; i < (int)v.size(); ++i)
      if (col_[v[i]] == 0) return false;
    return true;
  }

  std::vector<int> Split(int u) {
    if (col_[u] != 2) return {u};
    std::vector<int> ng;
    if (typ_[u] == 1) {  // Q-node
      if (!Check(g_[u])) {
        std::reverse(g_[u].begin(), g_[u].end());
        if (!Check(g_[u])) Fail();
      }
      for (int v : g_[u]) {
        if (col_[v] != 2) {
          ng.emplace_back(v);
        } else {
          auto sub = Split(v);
          ng.insert(ng.end(), sub.begin(), sub.end());
        }
      }
    } else {  // P-node
      std::vector<int> son[3];
      for (int x : g_[u]) son[col_[x]].emplace_back(x);
      if (son[2].size() > 1) Fail();
      if (!son[0].empty()) {
        int n0 = NewNode(0);
        g_[n0] = son[0];
        ng.emplace_back(n0);
      }
      if (!son[2].empty()) {
        auto sub = Split(son[2][0]);
        ng.insert(ng.end(), sub.begin(), sub.end());
      }
      if (!son[1].empty()) {
        int n1 = NewNode(0);
        g_[n1] = son[1];
        ng.emplace_back(n1);
      }
    }
    Delete(u);
    return ng;
  }

  void Work(int u) {
    if (col_[u] != 2) return;
    if (typ_[u] == 1) {  // Q-node
      int l = 1e9, r = -1e9;
      for (int i = 0; i < (int)g_[u].size(); ++i) {
        if (col_[g_[u][i]]) {
          l = std::min(l, i);
          r = std::max(r, i);
        }
      }
      for (int i = l + 1; i < r; ++i)
        if (col_[g_[u][i]] != 1) Fail();
      if (l == r && col_[g_[u][l]] == 2) {
        Work(g_[u][l]);
        return;
      }
      std::vector<int> ng;
      for (int i = 0; i < l; ++i) ng.emplace_back(g_[u][i]);
      auto left_split = Split(g_[u][l]);
      ng.insert(ng.end(), left_split.begin(), left_split.end());
      for (int i = l + 1; i < r; ++i) ng.emplace_back(g_[u][i]);
      if (l != r) {
        auto right_split = Split(g_[u][r]);
        std::reverse(right_split.begin(), right_split.end());
        ng.insert(ng.end(), right_split.begin(), right_split.end());
      }
      for (int i = r + 1; i < (int)g_[u].size(); ++i) ng.emplace_back(g_[u][i]);
      g_[u] = ng;
    } else {  // P-node
      std::vector<int> son[3];
      for (int x : g_[u]) son[col_[x]].emplace_back(x);
      if (son[1].empty() && son[2].size() == 1) {
        Work(son[2][0]);
        return;
      }
      g_[u].clear();
      if (son[2].size() > 2) Fail();
      g_[u] = son[0];
      int q_node = NewNode(1);
      g_[u].emplace_back(q_node);
      if (son[2].size() >= 1) {
        auto mid = Split(son[2][0]);
        g_[q_node].insert(g_[q_node].end(), mid.begin(), mid.end());
      }
      if (!son[1].empty()) {
        int black_root = NewNode(0);
        g_[q_node].emplace_back(black_root);
        g_[black_root] = son[1];
      }
      if (son[2].size() >= 2) {
        auto mid2 = Split(son[2][1]);
        std::reverse(mid2.begin(), mid2.end());
        g_[q_node].insert(g_[q_node].end(), mid2.begin(), mid2.end());
      }
    }
  }

  void Remove(int u) {
    for (auto& v : g_[u]) {
      int tv = v;
      while (g_[tv].size() == 1) {
        int t = tv;
        tv = g_[tv][0];
        Delete(t);
      }
      v = tv;
      Remove(v);
    }
  }

  void DfsAns(int u) {
    if (u >= 1 && u <= n_) {
      ans_.emplace_back(u);
      return;
    }
    for (int v : g_[u]) DfsAns(v);
  }
};