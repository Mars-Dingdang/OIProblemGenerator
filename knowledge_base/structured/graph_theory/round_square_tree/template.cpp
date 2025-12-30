#include <algorithm>
#include <vector>

const int MAXN = 100005;
const int MAXV = 2 * MAXN; // 圆方树点数最多为 2n

std::vector<int> G[MAXN], T[MAXV]; // 原图G，圆方树T
int dfn[MAXN], low[MAXN], dfc;
int stk[MAXN], tp;
int cnt; // 方点标号从 n+1 开始

void Tarjan(int u) {
    low[u] = dfn[u] = ++dfc;
    stk[++tp] = u;
    for (int v : G[u]) {
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = std::min(low[u], low[v]);
            if (low[v] == dfn[u]) { // 找到以 u 为根的点双
                T[++cnt].clear();
                int x;
                do {
                    x = stk[tp--];
                    T[cnt].push_back(x);
                    T[x].push_back(cnt);
                } while (x != v);
                T[cnt].push_back(u);
                T[u].push_back(cnt);
            }
        } else {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
}

// 构建圆方树主函数
void build_round_square_tree(int n, int m) {
    cnt = n; // 方点编号从 n+1 开始
    dfc = tp = 0;
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            Tarjan(i);
            --tp; // 弹出根节点
        }
    }
}