#include <bits/stdc++.h>
using namespace std;

// 计算 SG 函数（递归/记忆化）
// 假设状态用整数表示，后继函数为 vector<int> get_next_states(int state)
unordered_map<int, int> sg_memo;
int mex(const unordered_set<int>& vals) {
    int m = 0;
    while (vals.count(m)) ++m;
    return m;
}
int sg(int state) {
    if (sg_memo.count(state)) return sg_memo[state];
    vector<int> next_states = get_next_states(state); // 需根据具体游戏实现
    unordered_set<int> vals;
    for (int nxt : next_states) {
        vals.insert(sg(nxt));
    }
    return sg_memo[state] = mex(vals);
}

// Nim 游戏判断先手必胜
bool nim_win(const vector<int>& piles) {
    int xorsum = 0;
    for (int x : piles) xorsum ^= x;
    return xorsum != 0;
}

// Bachet 游戏（一堆石子，每次取 1..k 枚）
bool bachet_win(int n, int k) {
    return n % (k + 1) != 0;
}

// Moore's Nim-k 游戏
bool moore_nim_k_win(const vector<int>& piles, int k) {
    vector<int> cnt(32, 0); // 统计每位 1 的个数
    for (int x : piles) {
        for (int b = 0; b < 32; ++b) {
            if (x >> b & 1) cnt[b]++;
        }
    }
    for (int b = 0; b < 32; ++b) {
        if (cnt[b] % (k + 1) != 0) return true;
    }
    return false;
}

// 阶梯 Nim 游戏
bool staircase_nim_win(const vector<int>& piles) {
    int xorsum = 0;
    for (int i = 0; i < piles.size(); i += 2) { // 奇数堆（0‑based 索引）
        xorsum ^= piles[i];
    }
    return xorsum != 0;
}

// Wythoff 游戏（两堆石子）
bool wythoff_win(int a, int b) {
    if (a > b) swap(a, b);
    const double phi = (1.0 + sqrt(5.0)) / 2.0;
    int k = b - a;
    return a != (int)(k * phi); // 注意浮点误差，实际可用整数公式
}

int main() {
    // 示例：Nim 游戏
    vector<int> piles = {2, 5, 4};
    if (nim_win(piles)) {
        cout << "First player wins" << endl;
    } else {
        cout << "Second player wins" << endl;
    }
    return 0;
}