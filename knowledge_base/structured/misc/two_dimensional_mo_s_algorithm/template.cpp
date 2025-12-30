#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

const int MAXN = 201, MAXQ = 100001, MAXV = 40001;

int n, m, q, a[MAXN][MAXN];
long long ans[MAXQ];
int disc[MAXV], cntdisc;

int blocklen, counts[MAXV];
long long now;

struct Question {
    int x1, y1, x2, y2, qid;
    bool operator<(const Question& tmp) const {
        if (x1 / blocklen != tmp.x1 / blocklen) return x1 < tmp.x1;
        if (y1 / blocklen != tmp.y1 / blocklen) return y1 < tmp.y1;
        if (x2 / blocklen != tmp.x2 / blocklen) return x2 < tmp.x2;
        return y2 < tmp.y2;
    }
} Q[MAXQ];

int Qcnt;

void mo_algo_row(int id, int val, int Y1, int Y2) {
    for (int i = Y1; i <= Y2; ++i) {
        now -= (long long)counts[a[id][i]] * counts[a[id][i]];
        counts[a[id][i]] += val;
        now += (long long)counts[a[id][i]] * counts[a[id][i]];
    }
}

void mo_algo_column(int id, int val, int X1, int X2) {
    for (int i = X1; i <= X2; ++i) {
        now -= (long long)counts[a[i][id]] * counts[a[i][id]];
        counts[a[i][id]] += val;
        now += (long long)counts[a[i][id]] * counts[a[i][id]];
    }
}

void mo_algo() {
    blocklen = max((int)pow(n * m, 0.5) / pow(q, 0.25), 1);
    sort(Q + 1, Q + 1 + Qcnt);

    int X1 = 1, Y1 = 1, X2 = 0, Y2 = 0;
    for (int i = 1; i <= Qcnt; ++i) {
        while (X1 > Q[i].x1) mo_algo_row(--X1, 1, Y1, Y2);
        while (X2 < Q[i].x2) mo_algo_row(++X2, 1, Y1, Y2);
        while (Y1 > Q[i].y1) mo_algo_column(--Y1, 1, X1, X2);
        while (Y2 < Q[i].y2) mo_algo_column(++Y2, 1, X1, X2);
        while (X1 < Q[i].x1) mo_algo_row(X1++, -1, Y1, Y2);
        while (X2 > Q[i].x2) mo_algo_row(X2--, -1, Y1, Y2);
        while (Y1 < Q[i].y1) mo_algo_column(Y1++, -1, X1, X2);
        while (Y2 > Q[i].y2) mo_algo_column(Y2--, -1, X1, X2);
        ans[Q[i].qid] = now;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> a[i][j], disc[++cntdisc] = a[i][j];

    sort(disc + 1, disc + 1 + cntdisc);
    cntdisc = unique(disc + 1, disc + 1 + cntdisc) - disc - 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            a[i][j] = lower_bound(disc + 1, disc + 1 + cntdisc, a[i][j]) - disc;

    cin >> q;
    for (int i = 1; i <= q; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        Q[++Qcnt] = {x1, y1, x2, y2, i};
    }

    mo_algo();

    for (int i = 1; i <= q; ++i)
        cout << ans[i] << '\n';
    return 0;
}