#include <cmath>
#include <cstdio>
using namespace std;

constexpr int N = 200005;
constexpr int M = 450; // ~sqrt(N)

int n, m, nn, block_size, block_cnt, block_id[N], L[M], R[M];
int T[M][N]; // 分块外层 + 树状数组内层

int lb(int x) { return x & -x; }

void build(int n) {
    nn = n;
    block_size = sqrt(nn);
    block_cnt = nn / block_size;
    if (nn % block_size) block_cnt++;
    for (int i = 1; i <= block_cnt; ++i) {
        L[i] = (i - 1) * block_size + 1;
        R[i] = i * block_size;
    }
    R[block_cnt] = nn;
    for (int i = 1; i <= block_cnt; ++i)
        for (int j = L[i]; j <= R[i]; ++j)
            block_id[j] = i;
}

void add(int p, int v, int d) {
    for (int i = block_id[p]; i <= block_cnt; i += lb(i))
        for (int j = v; j <= nn; j += lb(j))
            T[i][j] += d;
}

int getsum(int p, int v) {
    if (!p || !v) return 0;
    int res = 0;
    int id = block_id[p];
    // 暴力处理不完整块
    for (int i = L[id]; i <= p; ++i)
        if (/* condition on value at i */ <= v) ++res;
    // 处理完整块：在外层树状数组上遍历
    for (int i = id - 1; i; i -= lb(i))
        for (int j = v; j; j -= lb(j))
            res += T[i][j];
    return res;
}

int query_range(int l, int r, int val) {
    if (l > r) return 0;
    return getsum(r, val) - getsum(l - 1, val);
}