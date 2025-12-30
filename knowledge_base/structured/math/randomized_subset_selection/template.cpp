#include <bits/stdc++.h>
using namespace std;

// 随机生成一个大小为 n/2 的子集（近似）
vector<int> randomSubsetSelection(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);
    
    vector<int> subset;
    // 第一步：随机选择每个元素，生成初始子集
    for (int i = 0; i < n; ++i) {
        if (dis(gen)) subset.push_back(i);
    }
    
    int target = n / 2;
    // 第二步：如果子集大小不足，随机添加元素
    while ((int)subset.size() < target) {
        int candidate = dis(gen) * n; // 简化示例，实际需确保不重复
        // 实际实现需检查 candidate 是否已在 subset 中
        subset.push_back(candidate);
    }
    
    // 第三步：如果子集大小超过，随机删除元素
    while ((int)subset.size() > target) {
        int idx = uniform_int_distribution<>(0, subset.size() - 1)(gen);
        subset.erase(subset.begin() + idx);
    }
    
    return subset;
}

int main() {
    int n = 100;
    vector<int> result = randomSubsetSelection(n);
    cout << "Selected " << result.size() << " elements.\n";
    return 0;
}