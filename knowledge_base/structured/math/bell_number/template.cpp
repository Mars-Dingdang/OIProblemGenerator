#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 5000;

// Compute Bell numbers up to n using Bell triangle
vector<int> bell_numbers(int n) {
    vector<vector<int>> bell(n + 1, vector<int>(n + 1, 0));
    bell[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        bell[i][0] = bell[i - 1][i - 1];
        for (int j = 1; j <= i; j++) {
            bell[i][j] = (bell[i][j - 1] + bell[i - 1][j - 1]) % MOD;
        }
    }
    
    vector<int> result(n + 1);
    for (int i = 0; i <= n; i++) {
        result[i] = bell[i][0];
    }
    return result;
}

// Alternative: using Stirling numbers of the second kind
vector<int> bell_numbers_stirling(int n) {
    vector<vector<int>> stirling(n + 1, vector<int>(n + 1, 0));
    stirling[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            stirling[i][j] = (stirling[i - 1][j - 1] + 1LL * j * stirling[i - 1][j]) % MOD;
        }
    }
    
    vector<int> bell(n + 1, 0);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            bell[i] = (bell[i] + stirling[i][j]) % MOD;
        }
    }
    return bell;
}

int main() {
    int n = 10;
    vector<int> bell = bell_numbers(n);
    
    for (int i = 0; i <= n; i++) {
        cout << "B[" << i << "] = " << bell[i] << endl;
    }
    
    return 0;
}