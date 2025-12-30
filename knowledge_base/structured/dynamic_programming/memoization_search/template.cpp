#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100;
const int MAX_T = 1000;
int n, T;
int w[MAX_N + 1], v[MAX_N + 1];
int memo[MAX_N + 2][MAX_T + 1]; // memo[pos][remaining_time]

int dfs(int pos, int tleft) {
    if (tleft < 0) return -1e9; // invalid state
    if (pos > n) return 0; // no more items
    if (memo[pos][tleft] != -1) return memo[pos][tleft]; // already computed
    
    // Option 1: skip current item
    int skip = dfs(pos + 1, tleft);
    // Option 2: take current item (if possible)
    int take = (tleft >= w[pos]) ? dfs(pos + 1, tleft - w[pos]) + v[pos] : -1e9;
    
    return memo[pos][tleft] = max(skip, take);
}

int main() {
    cin >> T >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i];
    }
    memset(memo, -1, sizeof(memo));
    cout << dfs(1, T) << endl;
    return 0;
}