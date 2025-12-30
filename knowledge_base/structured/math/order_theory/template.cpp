#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 示例：导弹拦截问题（Dilworth定理应用）
int main() {
    vector<int> a;
    int x;
    while (cin >> x) a.push_back(x);
    vector<int> f, g;
    for (int i : a) {
        // 最长不上升子序列（系统最多拦截导弹数）
        if (f.empty() || -i >= f.back())
            f.push_back(-i);
        else
            *upper_bound(f.begin(), f.end(), -i) = -i;
        // 最长上升子序列（最少系统数）
        if (g.empty() || i > g.back())
            g.push_back(i);
        else
            *lower_bound(g.begin(), g.end(), i) = i;
    }
    cout << f.size() << '\n' << g.size() << '\n';
    return 0;
}