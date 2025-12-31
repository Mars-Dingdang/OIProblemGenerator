struct LinearBasis {
    static const int M = 30; // 位数上限
    long long w[M];
    int p[M]; // 优先级，用于前缀线性基
    int c;   // 后导零个数（可选）

    LinearBasis() {
        for (int i = 0; i < M; ++i) w[i] = 0, p[i] = -1;
        c = 0;
    }

    // 普通插入
    bool insert(long long x) {
        for (int i = M - 1; i >= 0; --i) {
            if (!(x >> i & 1)) continue;
            if (!w[i]) {
                w[i] = x;
                return true;
            }
            x ^= w[i];
        }
        return false;
    }

    // 前缀线性基插入（带优先级）
    void insert_with_priority(long long x, int priority) {
        for (int i = M - 1; i >= 0; --i) {
            if (!(x >> i & 1)) continue;
            if (!w[i] || p[i] < priority) {
                swap(w[i], x);
                swap(p[i], priority);
            }
            x ^= w[i];
        }
        if (x) c++;
    }

    // 查询最大异或和
    long long max_xor() {
        long long res = 0;
        for (int i = M - 1; i >= 0; --i) {
            if ((res ^ w[i]) > res) res ^= w[i];
        }
        return res;
    }

    // 进一步消元（对角化）
    void eliminate_further() {
        for (int i = 0; i < M; ++i) {
            if (!w[i]) continue;
            for (int j = i + 1; j < M; ++j) {
                if (w[j] >> i & 1) w[j] ^= w[i];
            }
        }
    }
};