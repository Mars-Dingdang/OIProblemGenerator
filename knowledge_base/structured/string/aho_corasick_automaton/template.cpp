#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int N = 1e6 + 6;
const int SIZE = 1e6 + 6;

namespace AC {
    struct Node {
        int son[26];
        int cnt;
        int fail;
        void init() {
            memset(son, 0, sizeof(son));
            cnt = fail = 0;
        }
    } tr[SIZE];
    int tot;

    void init() {
        tot = 0;
        tr[0].init();
    }

    void insert(char s[]) {
        int u = 0;
        for (int i = 1; s[i]; i++) {
            int c = s[i] - 'a';
            if (!tr[u].son[c]) {
                tr[u].son[c] = ++tot;
                tr[tot].init();
            }
            u = tr[u].son[c];
        }
        tr[u].cnt++;
    }

    void build() {
        queue<int> q;
        for (int i = 0; i < 26; i++) {
            if (tr[0].son[i]) {
                q.push(tr[0].son[i]);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                if (tr[u].son[i]) {
                    tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
                    q.push(tr[u].son[i]);
                } else {
                    tr[u].son[i] = tr[tr[u].fail].son[i];
                }
            }
        }
    }

    int query(char t[]) {
        int u = 0, res = 0;
        for (int i = 1; t[i]; i++) {
            u = tr[u].son[t[i] - 'a'];
            for (int j = u; j && tr[j].cnt != -1; j = tr[j].fail) {
                res += tr[j].cnt;
                tr[j].cnt = -1;
            }
        }
        return res;
    }
}

char s[N];
int n;

int main() {
    AC::init();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        AC::insert(s);
    }
    AC::build();
    scanf("%s", s + 1);
    printf("%d\n", AC::query(s));
    return 0;
}