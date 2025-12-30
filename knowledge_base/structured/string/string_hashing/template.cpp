#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

struct StringHash {
    const ull base = 131;          // 常用质数 131, 13331
    vector<ull> pow, pref;         // 幂次表与前缀哈希表
    string s;
    
    StringHash(const string& str) : s(str) {
        int n = s.size();
        pow.resize(n + 1);
        pref.resize(n + 1);
        pow[0] = 1;
        pref[0] = 0;
        for (int i = 1; i <= n; ++i) {
            pow[i] = pow[i-1] * base;                 // 自然溢出，模 2^64
            pref[i] = pref[i-1] * base + s[i-1];      // 累积哈希
        }
    }
    
    // 获取子串 s[l..r] 的哈希值 (0-indexed)
    ull get(int l, int r) {
        return pref[r+1] - pref[l] * pow[r-l+1];
    }
};

// 双哈希版本（更安全）
struct DoubleHash {
    const ull base = 131;
    const ull mod1 = 1e9+7, mod2 = 1e9+9;
    vector<ull> pow1, pow2, pref1, pref2;
    string s;
    
    DoubleHash(const string& str) : s(str) {
        int n = s.size();
        pow1.resize(n+1); pow2.resize(n+1);
        pref1.resize(n+1); pref2.resize(n+1);
        pow1[0] = pow2[0] = 1;
        pref1[0] = pref2[0] = 0;
        for (int i = 1; i <= n; ++i) {
            pow1[i] = pow1[i-1] * base % mod1;
            pow2[i] = pow2[i-1] * base % mod2;
            pref1[i] = (pref1[i-1] * base + s[i-1]) % mod1;
            pref2[i] = (pref2[i-1] * base + s[i-1]) % mod2;
        }
    }
    
    pair<ull,ull> get(int l, int r) {
        ull h1 = (pref1[r+1] - pref1[l] * pow1[r-l+1] % mod1 + mod1) % mod1;
        ull h2 = (pref2[r+1] - pref2[l] * pow2[r-l+1] % mod2 + mod2) % mod2;
        return {h1, h2};
    }
};