#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 1000010;

char s[N];
int n, sa[N], rk[N << 1], oldrk[N << 1], id[N], cnt[N];

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    int m = 127;
    for (int i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
    memcpy(oldrk + 1, rk + 1, n * sizeof(int));
    int p = 0;
    for (int i = 1; i <= n; ++i) rk[sa[i]] = (oldrk[sa[i]] == oldrk[sa[i - 1]]) ? p : ++p;
    for (int w = 1; w < n; w <<= 1, m = p) {
        int cur = 0;
        for (int i = n - w + 1; i <= n; ++i) id[++cur] = i;
        for (int i = 1; i <= n; ++i) if (sa[i] > w) id[++cur] = sa[i] - w;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; ++i) ++cnt[rk[i]];
        for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];
        memcpy(oldrk, rk, sizeof(rk));
        p = 0;
        for (int i = 1; i <= n; ++i) {
            int x = sa[i], y = sa[i - 1];
            rk[sa[i]] = (oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w]) ? p : ++p;
        }
        if (p == n) break;
    }
    for (int i = 1; i <= n; ++i) printf("%d ", sa[i]);
    return 0;
}