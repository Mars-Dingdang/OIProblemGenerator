#include <vector>
#include <queue>
#include <cstring>
#include <climits>
using namespace std;

const int MAXN = 1e5 + 5;
const int INF = INT_MAX;

struct Edge {
    int to, weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

vector<Edge> graph[MAXN];
int indegree[MAXN];
int dist[MAXN];
int n, m;

void dag_dp(int start, bool find_longest = false) {
    // Initialize distances
    for (int i = 1; i <= n; ++i) {
        dist[i] = find_longest ? INT_MIN : INF;
    }
    dist[start] = 0;

    // Topological sort using Kahn's algorithm
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    // DP in topological order
    while (!q.empty()) {
        int u = q.front(); q.pop();

        int current_dist = dist[u];
        if (current_dist == (find_longest ? INT_MIN : INF)) continue;

        for (auto& edge : graph[u]) {
            int v = edge.to;
            int w = edge.weight;
            int new_dist = current_dist + w;

            if (find_longest) {
                if (new_dist > dist[v]) {
                    dist[v] = new_dist;
                }
            } else {
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                }
            }

            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }
}