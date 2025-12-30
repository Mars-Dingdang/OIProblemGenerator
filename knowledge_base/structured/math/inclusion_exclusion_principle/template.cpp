#include <bits/stdc++.h>
using namespace std;

// Example: Count number of integers in [1, n] divisible by any of given primes
long long inclusion_exclusion(const vector<long long>& primes, long long n) {
    int k = primes.size();
    long long ans = 0;
    for (int mask = 1; mask < (1 << k); ++mask) {
        long long lcm = 1;
        int bits = 0;
        for (int i = 0; i < k; ++i) {
            if (mask >> i & 1) {
                ++bits;
                lcm = lcm / __gcd(lcm, primes[i]) * primes[i];
                if (lcm > n) break; // overflow protection
            }
        }
        if (bits % 2 == 1) ans += n / lcm;
        else ans -= n / lcm;
    }
    return ans;
}

int main() {
    // Example usage
    vector<long long> primes = {2, 3, 5};
    long long n = 100;
    cout << inclusion_exclusion(primes, n) << endl; // numbers divisible by 2,3, or 5
    return 0;
}