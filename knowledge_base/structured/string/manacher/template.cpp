#include <bits/stdc++.h>
using namespace std;

// 标准 Manacher 算法，分别计算奇数长度和偶数长度回文半径
pair<vector<int>, vector<int>> manacher(const string &s) {
    int n = s.size();
    vector<int> d1(n), d2(n);
    // 奇数长度回文半径 d1[i]
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) {
            ++k;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    // 偶数长度回文半径 d2[i]
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) {
            ++k;
        }
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
    return {d1, d2};
}

// 统一处理版本（插入分隔符 '#'）
vector<int> manacher_unified(const string &s) {
    string t = "#";
    for (char c : s) {
        t += c;
        t += '#';
    }
    int n = t.size();
    vector<int> d1(n);
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && t[i - k] == t[i + k]) {
            ++k;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    // 如果需要，可以从 d1 恢复原字符串的奇偶半径
    return d1;
}

int main() {
    // 示例用法
    string s = "abababc";
    auto [d1, d2] = manacher(s);
    int total_palindromes = 0;
    for (int x : d1) total_palindromes += x;
    for (int x : d2) total_palindromes += x;
    cout << "Total palindromic substrings: " << total_palindromes << endl;
    return 0;
}