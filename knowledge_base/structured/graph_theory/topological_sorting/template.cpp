#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
vector<int> G[MAXN];
int in[MAXN];

bool toposort(int n, vector<int>& order) {
    order.clear();
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (in[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : G[u]) {
            if (--in[v] == 0) q.push(v);
        }
    }
    return order.size() == n;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        in[v]++;
    }
    vector<int> order;
    if (toposort(n, order)) {
        for (int x : order) cout << x << ' ';
        cout << endl;
    } else {
        cout << "Graph has a cycle!" << endl;
    }
    return 0;
}