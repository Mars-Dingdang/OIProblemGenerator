#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const int N = 100010;

struct node {
    int to, val;
};

vector<node> nbr[N];
int d1[N], d2[N], up[N];
int n;

void dfsd(int cur, int fa) {
    d1[cur] = d2[cur] = 0;
    for (node nxtn : nbr[cur]) {
        int nxt = nxtn.to, w = nxtn.val;
        if (nxt == fa) continue;
        dfsd(nxt, cur);
        if (d1[nxt] + w > d1[cur]) {
            d2[cur] = d1[cur];
            d1[cur] = d1[nxt] + w;
        } else if (d1[nxt] + w > d2[cur]) {
            d2[cur] = d1[nxt] + w;
        }
    }
}

void dfsu(int cur, int fa) {
    for (node nxtn : nbr[cur]) {
        int nxt = nxtn.to, w = nxtn.val;
        if (nxt == fa) continue;
        if (d1[cur] != d1[nxt] + w) {
            up[nxt] = max(up[cur], d1[cur]) + w;
        } else {
            up[nxt] = max(up[cur], d2[cur]) + w;
        }
        dfsu(nxt, cur);
    }
}

pair<int, int> getTreeCenter() {
    dfsd(1, 0);
    dfsu(1, 0);
    int min_max_len = INT_MAX;
    int center1 = -1, center2 = -1;
    for (int i = 1; i <= n; i++) {
        int max_len = max(d1[i], up[i]);
        if (max_len < min_max_len) {
            min_max_len = max_len;
            center1 = i;
            center2 = -1;
        } else if (max_len == min_max_len) {
            center2 = i;
        }
    }
    return {center1, center2};
}