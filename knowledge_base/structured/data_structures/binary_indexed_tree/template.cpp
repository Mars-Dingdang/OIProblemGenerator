#include <vector>
using namespace std;

template<typename T>
class BIT {
private:
    vector<T> tree;
    int n;
    int lowbit(int x) { return x & -x; }
public:
    BIT(int size) : n(size), tree(size + 1, 0) {}
    // 单点加值
    void add(int x, T v) {
        while (x <= n) {
            tree[x] += v;
            x += lowbit(x);
        }
    }
    // 前缀和查询 [1..x]
    T sum(int x) {
        T res = 0;
        while (x > 0) {
            res += tree[x];
            x -= lowbit(x);
        }
        return res;
    }
    // 区间和查询 [l..r]
    T range_sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    // 区间加值（差分实现）
    void range_add(int l, int r, T v) {
        add(l, v);
        add(r + 1, -v);
    }
    // 单点查询（差分实现）
    T point_query(int x) {
        return sum(x);
    }
    // 区间加 & 区间和（两个BIT维护）
    void range_add_range_sum_init() {
        // 需要两个BIT: bit1维护d[i], bit2维护d[i]*i
        // 见完整实现
    }
};

// 二维树状数组（单点修改，子矩阵查询）
template<typename T>
class BIT2D {
private:
    vector<vector<T>> tree;
    int n, m;
    int lowbit(int x) { return x & -x; }
public:
    BIT2D(int rows, int cols) : n(rows), m(cols), tree(rows + 1, vector<T>(cols + 1, 0)) {}
    void add(int x, int y, T v) {
        for (int i = x; i <= n; i += lowbit(i))
            for (int j = y; j <= m; j += lowbit(j))
                tree[i][j] += v;
    }
    T sum(int x, int y) {
        T res = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            for (int j = y; j > 0; j -= lowbit(j))
                res += tree[i][j];
        return res;
    }
    T query(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
    }
};