struct PalindromeTree {
    static const int MAXN = 300010;
    static const int SIGMA = 26;

    int n, last, sz;
    int s[MAXN]; // 输入字符存储（1-indexed）
    int len[MAXN], fail[MAXN], cnt[MAXN];
    int go[MAXN][SIGMA];

    // 初始化两个根
    void init() {
        n = 0; last = 0;
        sz = 2;
        len[0] = 0; fail[0] = 1; // even
        len[1] = -1; fail[1] = 1; // odd
        memset(go[0], 0, sizeof(go[0]));
        memset(go[1], 0, sizeof(go[1]));
    }

    // 获取 x 的最长回文后缀，使其前面可以接字符 c
    int get_fail(int x) {
        while (s[n] != s[n - len[x] - 1]) x = fail[x];
        return x;
    }

    void add(char ch) {
        int c = ch - 'a';
        s[++n] = c;
        int cur = get_fail(last);
        if (!go[cur][c]) {
            int now = sz++;
            len[now] = len[cur] + 2;
            fail[now] = go[get_fail(fail[cur])][c];
            if (!fail[now]) fail[now] = 0;
            memset(go[now], 0, sizeof(go[now]));
            go[cur][c] = now;
        }
        last = go[cur][c];
        cnt[last]++;
    }

    // 统计每个节点的实际出现次数
    void count() {
        for (int i = sz - 1; i >= 0; i--) {
            cnt[fail[i]] += cnt[i];
        }
    }
};