#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 1e5 + 5;

int n, m;
vector<int> G[MAXN];
int in[MAXN]; // 入度数组

bool toposort(vector<int>& L) {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        L.push_back(u);
        for (int v : G[u]) {
            if (--in[v] == 0) {
                q.push(v);
            }
        }
    }

    return L.size() == n;
}