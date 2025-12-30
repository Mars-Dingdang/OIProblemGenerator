#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int N = 5e5 + 5, M = 2e6 + 5;

int n, m;
struct Edge { int to, next; } e[M << 1];
int head[N], tot = 1;
void add_edge(int u, int v) {
    e[++tot] = {v, head[u]};
    head[u] = tot;
}

// 边双连通分量 - Tarjan 算法（基于栈）
int dfn[N], low[N], bcc_cnt;
bool visited[N];
vector<vector<int>> edge_bcc;
stack<int> st;

void tarjan_edge_bcc(int u, int parent_edge) {
    dfn[u] = low[u] = ++bcc_cnt;
    st.push(u);
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (i == (parent_edge ^ 1)) continue;
        if (!dfn[v]) {
            tarjan_edge_bcc(v, i);
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        vector<int> comp;
        while (true) {
            int node = st.top(); st.pop();
            comp.push_back(node);
            if (node == u) break;
        }
        edge_bcc.push_back(comp);
    }
}

// 点双连通分量 - Tarjan 算法
int dfn2[N], low2[N], bcc_cnt2;
bool cut[N];
vector<int> dcc[N];
int stk[N], top2;
int root2;

void tarjan_point_bcc(int u) {
    dfn2[u] = low2[u] = ++bcc_cnt2;
    stk[++top2] = u;
    if (u == root2 && head[u] == 0) { // 孤立点
        dcc[++cnt].push_back(u);
        return;
    }
    int child = 0;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (!dfn2[v]) {
            tarjan_point_bcc(v);
            low2[u] = min(low2[u], low2[v]);
            if (low2[v] >= dfn2[u]) {
                child++;
                if (u != root2 || child > 1) cut[u] = true;
                cnt++;
                do {
                    dcc[cnt].push_back(stk[top2--]);
                } while (stk[top2 + 1] != v);
                dcc[cnt].push_back(u);
            }
        } else {
            low2[u] = min(low2[u], dfn2[v]);
        }
    }
}