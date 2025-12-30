#include <bits/stdc++.h>
using namespace std;

// 计算前缀函数
vector<int> prefix_function(const string& s) {
    int n = (int)s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

// KMP 查找所有匹配位置
vector<int> kmp_find(const string& text, const string& pattern) {
    string cur = pattern + '#' + text;
    int n = pattern.size(), m = text.size();
    vector<int> pi = prefix_function(cur);
    vector<int> occurrences;
    for (int i = n + 1; i <= n + m; ++i) {
        if (pi[i] == n) {
            occurrences.push_back(i - 2 * n);
        }
    }
    return occurrences;
}

// 统计每个前缀在自身中的出现次数
vector<long long> prefix_occurrences(const string& s) {
    int n = s.size();
    vector<int> pi = prefix_function(s);
    vector<long long> ans(n + 1);
    for (int i = 0; i < n; ++i) ans[pi[i]]++;
    for (int i = n - 1; i > 0; --i) ans[pi[i - 1]] += ans[i];
    for (int i = 0; i <= n; ++i) ans[i]++;
    return ans;
}

// 构建前缀函数自动机 (仅小写字母)
vector<vector<int>> build_automaton(const string& s) {
    string t = s + '#';
    int n = t.size();
    vector<int> pi = prefix_function(t);
    vector<vector<int>> aut(n, vector<int>(26));
    for (int i = 0; i < n; ++i) {
        for (int c = 0; c < 26; ++c) {
            if (i > 0 && 'a' + c != t[i])
                aut[i][c] = aut[pi[i - 1]][c];
            else
                aut[i][c] = i + ('a' + c == t[i]);
        }
    }
    return aut;
}

int main() {
    // 示例用法
    string text = "ababcababcab";
    string pattern = "abc";
    vector<int> matches = kmp_find(text, pattern);
    for (int pos : matches) cout << pos << ' ';
    cout << endl;
    return 0;
}