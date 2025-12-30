#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

// 双向 BFS 模板（以状态为整数为例）
int bidirectional_bfs(int start, int target, int n) {
    if (start == target) return 0;
    queue<int> q_front, q_back;
    unordered_map<int, int> dist_front, dist_back;
    q_front.push(start); dist_front[start] = 0;
    q_back.push(target); dist_back[target] = 0;
    
    while (!q_front.empty() && !q_back.empty()) {
        // 扩展正向队列
        int size = q_front.size();
        for (int i = 0; i < size; ++i) {
            int cur = q_front.front(); q_front.pop();
            // 生成下一个状态（示例：cur+1, cur-1）
            vector<int> next_states = {cur + 1, cur - 1};
            for (int next : next_states) {
                if (next < 1 || next > n) continue;
                if (dist_back.count(next)) {
                    return dist_front[cur] + 1 + dist_back[next];
                }
                if (!dist_front.count(next)) {
                    dist_front[next] = dist_front[cur] + 1;
                    q_front.push(next);
                }
            }
        }
        // 扩展反向队列
        size = q_back.size();
        for (int i = 0; i < size; ++i) {
            int cur = q_back.front(); q_back.pop();
            vector<int> next_states = {cur + 1, cur - 1};
            for (int next : next_states) {
                if (next < 1 || next > n) continue;
                if (dist_front.count(next)) {
                    return dist_back[cur] + 1 + dist_front[next];
                }
                if (!dist_back.count(next)) {
                    dist_back[next] = dist_back[cur] + 1;
                    q_back.push(next);
                }
            }
        }
    }
    return -1; // 未找到路径
}

int main() {
    // 示例用法
    int start = 1, target = 100, n = 100;
    int ans = bidirectional_bfs(start, target, n);
    cout << ans << endl;
    return 0;
}