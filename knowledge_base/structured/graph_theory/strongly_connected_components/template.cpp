// Tarjan's Algorithm for Strongly Connected Components
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5; // Adjust size as needed
int dfn[N], low[N], dfncnt;
int scc[N], sc; // scc[i]: which SCC node i belongs to
int sz[N];     // sz[i]: size of SCC i
bool in_stack[N];
stack<int> stk;
vector<int> g[N]; // adjacency list

void tarjan(int u) {
    dfn[u] = low[u] = ++dfncnt;
    stk.push(u);
    in_stack[u] = true;

    for (int v : g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        ++sc;
        int node;
        do {
            node = stk.top();
            stk.pop();
            in_stack[node] = false;
            scc[node] = sc;
            sz[sc]++;
        } while (node != u);
    }
}

// Call tarjan(i) for all unvisited nodes
void find_scc(int n) {
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
}