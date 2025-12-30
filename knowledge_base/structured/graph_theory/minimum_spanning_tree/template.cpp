#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
const int MAXM = 200010;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

Edge edges[MAXM];
int parent[MAXN];
int n, m;

int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void merge(int x, int y) {
    x = find(x), y = find(y);
    parent[x] = y;
}

long long kruskal() {
    sort(edges + 1, edges + m + 1);
    for (int i = 1; i <= n; ++i) parent[i] = i;
    long long total_weight = 0;
    int edges_used = 0;
    for (int i = 1; i <= m; ++i) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (find(u) != find(v)) {
            merge(u, v);
            total_weight += w;
            edges_used++;
            if (edges_used == n - 1) break;
        }
    }
    return edges_used == n - 1 ? total_weight : -1; // -1 表示不连通
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    cout << kruskal() << endl;
    return 0;
}