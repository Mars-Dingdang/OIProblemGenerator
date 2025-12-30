#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
const int MAXLOG = 18;

int tree[MAXLOG][MAXN];
int toleft[MAXLOG][MAXN];
int sorted[MAXN];

void build(int left, int right, int deep) {
    if (left == right) return;
    int mid = (left + right) >> 1;
    int same = mid - left + 1;
    for (int i = left; i <= right; ++i) {
        if (tree[deep][i] < sorted[mid]) --same;
    }
    int ls = left, rs = mid + 1;
    for (int i = left; i <= right; ++i) {
        int flag = 0;
        if ((tree[deep][i] < sorted[mid]) || (tree[deep][i] == sorted[mid] && same > 0)) {
            flag = 1;
            tree[deep+1][ls++] = tree[deep][i];
            if (tree[deep][i] == sorted[mid]) --same;
        } else {
            tree[deep+1][rs++] = tree[deep][i];
        }
        toleft[deep][i] = toleft[deep][i-1] + flag;
    }
    build(left, mid, deep+1);
    build(mid+1, right, deep+1);
}

int query(int left, int right, int k, int l, int r, int deep) {
    if (l == r) return tree[deep][l];
    int mid = (l + r) >> 1;
    int x = toleft[deep][left-1] - toleft[deep][l-1];
    int y = toleft[deep][right] - toleft[deep][l-1];
    int cnt = y - x;
    if (cnt >= k) {
        int new_left = l + x;
        int new_right = l + y - 1;
        return query(new_left, new_right, k, l, mid, deep+1);
    } else {
        int rx = left - l - x;
        int ry = right - l - y;
        return query(mid + rx + 1, mid + ry + 1, k - cnt, mid+1, r, deep+1);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    // Example usage
    return 0;
}