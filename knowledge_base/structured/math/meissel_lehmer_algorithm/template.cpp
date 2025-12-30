#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// Helper: linear sieve for primes up to N
vector<int> linear_sieve(int N, vector<int>& primes) {
    vector<int> lpf(N + 1, 0);
    primes.clear();
    for (int i = 2; i <= N; ++i) {
        if (lpf[i] == 0) {
            lpf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > lpf[i] || i * p > N) break;
            lpf[i * p] = p;
        }
    }
    return lpf;
}

// π(x) for x <= limit using precomputed primes
int prime_pi(const vector<int>& primes, i64 x) {
    if (x < 2) return 0;
    return upper_bound(primes.begin(), primes.end(), x) - primes.begin();
}

// Meissel-Lehmer main function
i64 meissel_lehmer(i64 n) {
    if (n < 2) return 0;
    i64 y = pow(n, 1.0/3) * pow(log(n), 3) * log(log(n));
    y = max(y, 2LL);
    int a = prime_pi(primes, y);

    // Precompute primes up to sqrt(n)
    vector<int> primes;
    linear_sieve(sqrt(n) + 5, primes);

    // Compute φ(x, a) using recursion with memoization
    map<pair<i64, int>, i64> phi_cache;
    function<i64(i64, int)> phi = [&](i64 x, int a) -> i64 {
        if (a == 0) return x;
        if (x < primes[a-1]) return 1;
        auto key = make_pair(x, a);
        if (phi_cache.count(key)) return phi_cache[key];
        return phi_cache[key] = phi(x, a-1) - phi(x / primes[a-1], a-1);
    };

    // Compute P₂(x, a)
    i64 p2 = 0;
    for (int i = a; i < primes.size() && (i64)primes[i] * primes[i] <= n; ++i) {
        i64 p = primes[i];
        p2 += prime_pi(primes, n / p) - prime_pi(primes, p) + 1;
    }

    i64 res = phi(n, a) + a - 1 - p2;
    return res;
}

int main() {
    i64 n;
    cin >> n;
    cout << meissel_lehmer(n) << endl;
    return 0;
}