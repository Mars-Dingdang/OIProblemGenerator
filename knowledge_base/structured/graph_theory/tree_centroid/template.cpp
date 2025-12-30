#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 50005;
int n;
int siz[MAXN], weight[MAXN];
vector<int> centroids;
vector<int> g[MAXN];

void dfs(int cur, int fa) {
    siz[cur] = 1;
    weight[cur] = 0;
    for (int v : g[cur]) {
        if (v != fa) {
            dfs(v, cur);
            siz[cur] += siz[v];
            weight[cur] = max(weight[cur], siz[v]);
        }
    }
    weight[cur] = max(weight[cur], n - siz[cur]);
    if (weight[cur] <= n / 2) {
        centroids.push_back(cur);
    }
}

void get_centroids() {
    dfs(1, 0);
}