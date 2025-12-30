#include <vector>
#include <queue>
#include <iostream>
using namespace std;

const int MAXN = 100005;
vector<int> graph[MAXN];
int indegree[MAXN];
int n, m;

void topologicalSort() {
    priority_queue<int, vector<int>, greater<int>> pq; // 最小堆 -> 字典序最小
    // 若求字典序最大，改为: priority_queue<int> pq;

    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            pq.push(i);
        }
    }

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        cout << u << " ";

        for (int v : graph[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                pq.push(v);
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        indegree[v]++;
    }

    topologicalSort();
    return 0;
}