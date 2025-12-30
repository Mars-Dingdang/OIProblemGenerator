#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> path;          // 当前路径
vector<bool> visited;      // 访问标记
int n;                     // 问题规模

void dfs(int step) {
    // 边界条件：找到一组解
    if (step == n) {
        for (int x : path) cout << x << ' ';
        cout << endl;
        return;
    }
    
    // 遍历所有可能的选择
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {          // 剪枝：避免重复选择
            visited[i] = true;      // 做出选择
            path.push_back(i);      // 记录路径
            
            dfs(step + 1);          // 递归进入下一层
            
            path.pop_back();        // 撤销选择（回溯）
            visited[i] = false;
        }
    }
}

int main() {
    cin >> n;
    visited.resize(n, false);
    dfs(0);
    return 0;
}