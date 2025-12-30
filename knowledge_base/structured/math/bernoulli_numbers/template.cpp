using ll = long long;
constexpr int MAXN = 10000;
constexpr int mod = 1e9 + 7;
ll B[MAXN];        // 伯努利数
ll C[MAXN][MAXN];  // 组合数
ll inv[MAXN];      // 逆元

void init() {
  // 预处理组合数
  for (int i = 0; i < MAXN; i++) {
    C[i][0] = C[i][i] = 1;
    for (int k = 1; k < i; k++) {
      C[i][k] = (C[i - 1][k] % mod + C[i - 1][k - 1] % mod) % mod;
    }
  }
  // 预处理逆元
  inv[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
  }
  // 预处理伯努利数
  B[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    ll ans = 0;
    if (i == MAXN - 1) break;
    for (int k = 0; k < i; k++) {
      ans += C[i + 1][k] * B[k];
      ans %= mod;
    }
    ans = (ans * (-inv[i + 1]) % mod + mod) % mod;
    B[i] = ans;
  }
}

// 计算 S_m(n) = 0^m + 1^m + ... + (n-1)^m
ll power_sum(ll m, ll n) {
  n %= mod;
  ll res = 0;
  ll npow = n; // n^{m+1-k}
  for (int k = 0; k <= m; k++) {
    ll coeff = C[m + 1][k] * B[k] % mod;
    res = (res + coeff * npow) % mod;
    npow = npow * n % mod;
  }
  res = res * inv[m + 1] % mod;
  return res;
}