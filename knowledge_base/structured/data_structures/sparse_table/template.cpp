#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#if defined(_MSC_VER) && !defined(__clang__)
#include <immintrin.h>
#define __builtin_clz _lzcnt_u32
#endif
using namespace std;

int lg2(int x) { return 31 - __builtin_clz(x); }

template <typename T>
class SparseTable {
  using VT = vector<T>;
  using VVT = vector<VT>;
  using func_type = function<T(const T &, const T &)>>;

  VVT ST;
  vector<int> Log;
  func_type op;

  static T default_func(const T &t1, const T &t2) { return max(t1, t2); }

 public:
  SparseTable(const vector<T> &v, func_type _func = default_func) : op(_func) {
    int n = v.size();
    Log.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
      Log[i] = Log[i / 2] + 1;
    }
    int l = lg2(n);
    ST.assign(l + 1, VT(n));
    for (int i = 0; i < n; ++i) {
      ST[0][i] = v[i];
    }
    for (int j = 1; j <= l; ++j) {
      for (int i = 0; i + (1 << j) <= n; ++i) {
        ST[j][i] = op(ST[j - 1][i], ST[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T query(int l, int r) {
    int j = Log[r - l + 1];
    return op(ST[j][l], ST[j][r - (1 << j) + 1]);
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int &i : a) cin >> i;
  SparseTable<int> st(a);
  while (m--) {
    int l, r;
    cin >> l >> r;
    cout << st.query(l - 1, r - 1) << '\n';
  }
  return 0;
}