#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 100001;
const int MAXM = 200001;

int deg[MAXN];
vector<int> E[MAXN], E1[MAXN];
long long cnt[MAXN], total = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        E[u].push_back(v);
        E[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    // 建立定向图：从小度数到大度数，同度按编号小到大
    for (int u = 1; u <= n; u++) {
        for (int v : E[u]) {
            if (make_pair(deg[u], u) < make_pair(deg[v], v)) {
                E1[u].push_back(v);
            }
        }
    }

    // 四元环计数
    for (int a = 1; a <= n; a++) {
        for (int b : E1[a]) {
            for (int c : E1[b]) {
                if (make_pair(deg[a], a) >= make_pair(deg[c], c)) {
                    total += cnt[c];
                    cnt[c]++;
                }
            }
        }
        for (int b : E1[a]) {
            for (int c : E1[b]) {
                if (make_pair(deg[a], a) >= make_pair(deg[c], c)) {
                    cnt[c] = 0;
                }
            }
        }
    }

    cout << total << '\n';
    return 0;
}