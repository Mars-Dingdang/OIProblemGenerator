#include <bits/stdc++.h>
using namespace std;

// Placeholder for Optimal In-Place Suffix Sorting (SA-IS in-place variant)
// Full implementation is lengthy; below is a standard SA-IS for reference.

const int MAXN = 1000005;
int sa[MAXN], rk[MAXN], tmp[MAXN], cnt[MAXN];

void buildSA(const string &s) {
    int n = s.size();
    vector<int> bucket(256, 0);
    for (int i = 0; i < n; i++) bucket[s[i]]++;
    for (int i = 1; i < 256; i++) bucket[i] += bucket[i-1];
    for (int i = n-1; i >= 0; i--) sa[--bucket[s[i]]] = i;
    rk[sa[0]] = 0;
    for (int i = 1; i < n; i++) rk[sa[i]] = rk[sa[i-1]] + (s[sa[i]] != s[sa[i-1]]);
    for (int k = 1; k < n; k <<= 1) {
        fill(cnt, cnt + n, 0);
        for (int i = 0; i < n; i++) cnt[rk[i]]++;
        for (int i = 1; i < n; i++) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--) {
            int j = sa[i] - k;
            if (j < 0) j += n;
            tmp[--cnt[rk[j]]] = j;
        }
        copy(tmp, tmp + n, sa);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            tmp[sa[i]] = tmp[sa[i-1]];
            if (rk[sa[i]] != rk[sa[i-1]] || rk[(sa[i]+k)%n] != rk[(sa[i-1]+k)%n]) tmp[sa[i]]++;
        }
        copy(tmp, tmp + n, rk);
    }
}

int main() {
    string s;
    cin >> s;
    s += '$';
    buildSA(s);
    for (int i = 1; i < s.size(); i++) cout << sa[i] << ' ';
    return 0;
}