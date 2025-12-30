#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

struct LinearBasis {
    static const int MAXL = 60; // 最大位数
    ull p[MAXL];
    LinearBasis() { memset(p, 0, sizeof(p)); }
    
    // 插入一个数 x
    bool insert(ull x) {
        for (int i = MAXL-1; i >= 0; --i) {
            if (!(x >> i)) continue;
            if (!p[i]) {
                p[i] = x;
                return true;
            }
            x ^= p[i];
        }
        return false; // x 被异或成 0，说明能被表示
    }
    
    // 查询最大异或和
    ull query_max() {
        ull res = 0;
        for (int i = MAXL-1; i >= 0; --i) {
            if ((res ^ p[i]) > res) res ^= p[i];
        }
        return res;
    }
    
    // 查询最小异或和（非空子集）
    ull query_min() {
        for (int i = 0; i < MAXL; ++i) {
            if (p[i]) return p[i];
        }
        return 0;
    }
    
    // 重构为简化阶梯形（高斯消元法）
    void rebuild() {
        for (int i = MAXL-1; i >= 0; --i) {
            for (int j = i-1; j >= 0; --j) {
                if ((p[i] >> j) & 1) p[i] ^= p[j];
            }
        }
    }
    
    // 查询第 k 小异或和（需要先 rebuild）
    ull kth(ull k) {
        vector<ull> v;
        for (int i = 0; i < MAXL; ++i) {
            if (p[i]) v.push_back(p[i]);
        }
        ull res = 0;
        for (int i = 0; i < (int)v.size(); ++i) {
            if ((k >> i) & 1) res ^= v[i];
        }
        return res;
    }
    
    // 合并另一个线性基
    void merge(const LinearBasis &other) {
        for (int i = MAXL-1; i >= 0; --i) {
            if (other.p[i]) insert(other.p[i]);
        }
    }
};

int main() {
    int n;
    cin >> n;
    LinearBasis lb;
    for (int i = 0; i < n; ++i) {
        ull x;
        cin >> x;
        lb.insert(x);
    }
    cout << lb.query_max() << endl;
    return 0;
}