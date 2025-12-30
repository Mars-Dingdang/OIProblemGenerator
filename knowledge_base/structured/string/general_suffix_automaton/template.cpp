#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000000;  // 双倍字符串长度
const int CHAR_NUM = 26;   // 字符集大小，小写字母

struct exSAM {
    int len[MAXN];             // 节点长度
    int link[MAXN];            // 后缀链接
    int next[MAXN][CHAR_NUM];  // 转移
    int tot;                   // 节点总数：[0, tot)

    void init() {
        tot = 1;
        link[0] = -1;
        memset(next[0], 0, sizeof(next[0]));
    }

    int insertSAM(int last, int c) {
        int cur = next[last][c];
        if (len[cur]) return cur;
        len[cur] = len[last] + 1;
        int p = link[last];
        while (p != -1) {
            if (!next[p][c])
                next[p][c] = cur;
            else
                break;
            p = link[p];
        }
        if (p == -1) {
            link[cur] = 0;
            return cur;
        }
        int q = next[p][c];
        if (len[p] + 1 == len[q]) {
            link[cur] = q;
            return cur;
        }
        int clone = tot++;
        for (int i = 0; i < CHAR_NUM; ++i)
            next[clone][i] = len[next[q][i]] != 0 ? next[q][i] : 0;
        len[clone] = len[p] + 1;
        while (p != -1 && next[p][c] == q) {
            next[p][c] = clone;
            p = link[p];
        }
        link[clone] = link[q];
        link[cur] = clone;
        link[q] = clone;
        return cur;
    }

    int insertTrie(int cur, int c) {
        if (!next[cur][c]) {
            next[cur][c] = tot++;
            memset(next[next[cur][c]], 0, sizeof(next[0]));
            len[next[cur][c]] = 0;
            link[next[cur][c]] = -1;
        }
        return next[cur][c];
    }

    void insert(const string &s) {
        int root = 0;
        for (char ch : s) root = insertTrie(root, ch - 'a');
    }

    void build() {
        queue<pair<int, int>> q;
        for (int i = 0; i < CHAR_NUM; ++i)
            if (next[0][i]) q.push({i, 0});
        while (!q.empty()) {
            auto [c, last] = q.front(); q.pop();
            int newLast = insertSAM(last, c);
            for (int i = 0; i < CHAR_NUM; ++i)
                if (next[newLast][i]) q.push({i, newLast});
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    exSAM sam;
    sam.init();

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        sam.insert(s);
    }
    sam.build();

    // 计算所有字符串不同子串总数
    long long ans = 0;
    for (int i = 1; i < sam.tot; ++i)
        ans += sam.len[i] - sam.len[sam.link[i]];
    cout << ans << '\n';

    return 0;
}