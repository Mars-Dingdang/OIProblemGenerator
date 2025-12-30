#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;
vector<int> g[N];
int dp[N][2]; // 示例状态：dp[u][0/1] 表示节点 u 不选/选时的最优值

void dfs(int u, int parent) {
    // 初始化或处理叶子节点
    for (int v : g[u]) {
        if (v == parent) continue;
        dfs(v, u);
        // 状态转移
        // 例如：dp[u][0] += max(dp[v][0], dp[v][1]);
        //       dp[u][1] += dp[v][0];
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    cout << max(dp[1][0], dp[1][1]) << endl;
    return 0;
}