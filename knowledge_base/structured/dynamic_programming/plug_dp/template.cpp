#include <bits/stdc++.h>
using namespace std;

const int N = 11, M = 11;
const int offset = 2, mask = (1 << offset) - 1;
int n, m;
long long ans, d;
const int MaxSZ = 16796, Prime = 9973;

struct HashTable {
    int head[Prime], next[MaxSZ], sz;
    int state[MaxSZ];
    long long key[MaxSZ];
    
    void clear() {
        sz = 0;
        memset(head, -1, sizeof(head));
    }
    
    void push(int s, long long val) {
        int x = s % Prime;
        for (int i = head[x]; ~i; i = next[i]) {
            if (state[i] == s) {
                key[i] += val;
                return;
            }
        }
        state[sz] = s;
        key[sz] = val;
        next[sz] = head[x];
        head[x] = sz++;
    }
    
    void roll() {
        for (int i = 0; i < sz; i++) state[i] <<= offset;
    }
} H[2], *H0, *H1;

int b[M + 1], bb[M + 1];

int encode() {
    int s = 0;
    memset(bb, -1, sizeof(bb));
    int bn = 1;
    bb[0] = 0;
    for (int i = m; i >= 0; --i) {
        if (!~bb[b[i]]) bb[b[i]] = bn++;
        s <<= offset;
        s |= bb[b[i]];
    }
    return s;
}

void decode(int s) {
    for (int i = 0; i <= m; i++) {
        b[i] = s & mask;
        s >>= offset;
    }
}

void push(int j, int dn, int rt) {
    b[j] = dn;
    b[j + 1] = rt;
    H1->push(encode(), d);
}

int main() {
    cin >> n >> m;
    if (m > n) swap(n, m);
    H0 = H, H1 = H + 1;
    H1->clear();
    d = 1;
    H1->push(0, 1);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            swap(H0, H1);
            H1->clear();
            for (int k = 0; k < H0->sz; k++) {
                decode(H0->state[k]);
                d = H0->key[k];
                int lt = b[j], up = b[j + 1];
                bool dn = i != n - 1, rt = j != m - 1;
                
                if (lt && up) {
                    if (lt == up) {
                        if (i == n - 1 && j == m - 1) {
                            push(j, 0, 0);
                        }
                    } else {
                        for (int t = 0; t <= m; t++)
                            if (b[t] == lt) b[t] = up;
                        push(j, 0, 0);
                    }
                } else if (lt || up) {
                    int t = lt | up;
                    if (dn) push(j, t, 0);
                    if (rt) push(j, 0, t);
                } else {
                    if (dn && rt) push(j, m, m);
                }
            }
        }
        H1->roll();
    }
    
    cout << (H1->sz == 1 ? H1->key[0] : 0) << endl;
    return 0;
}