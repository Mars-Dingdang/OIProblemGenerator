const int MAXN = 1e5 + 5;
const int LOGN = 17;

struct CatTree {
    int n, log_len[MAXN];
    vector<int> data;
    vector<vector<int>> pre[LOGN], suf[LOGN];

    void build(vector<int>& arr) {
        n = arr.size();
        data = arr;
        for (int i = 2; i < MAXN; i++)
            log_len[i] = log_len[i >> 1] + 1;

        int k = log_len[n] + 1;
        pre[k].resize(1 << k);
        suf[k].resize(1 << k);

        function<void(int, int, int)> build_rec = [&](int l, int r, int dep) {
            if (l == r) return;
            int mid = (l + r) >> 1;
            // Build prefix and suffix arrays
            pre[dep][l] = data[l];
            for (int i = l + 1; i <= mid; i++)
                pre[dep][i] = merge(pre[dep][i - 1], data[i]);
            suf[dep][r] = data[r];
            for (int i = r - 1; i > mid; i--)
                suf[dep][i] = merge(data[i], suf[dep][i + 1]);
            build_rec(l, mid, dep + 1);
            build_rec(mid + 1, r, dep + 1);
        };
        build_rec(0, n - 1, 0);
    }

    // Dummy merge function (to be replaced based on use case e.g. sum, xor, matrix)
    int merge(int a, int b) { return a + b; }

    int query(int l, int r) {
        if (l == r) return data[l];
        int dep = log_len[l ^ r];
        int mid = (l + r) >> 1;
        return merge(suf[dep][l], pre[dep][r]);
    }
};