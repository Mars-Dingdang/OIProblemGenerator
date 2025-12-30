#include <vector>
using namespace std;

const int MAXN = 100010;

int n;
int c[MAXN];

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int k) {
    while (x <= n) {
        c[x] += k;
        x += lowbit(x);
    }
}

int getsum(int x) {
    int ans = 0;
    while (x > 0) {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}

// 区间查询 [l, r]
int range_query(int l, int r) {
    return getsum(r) - getsum(l - 1);
}