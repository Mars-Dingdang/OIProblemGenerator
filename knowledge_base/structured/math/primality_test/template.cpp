#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

long long quickPow(long long a, long long b, long long mod) {
    long long res = 1 % mod;
    while (b) {
        if (b & 1) res = (__int128)res * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return res;
}

bool millerRabin(long long n) {
    if (n < 3 || n % 2 == 0) return n == 2;
    long long u = n - 1, t = 0;
    while (u % 2 == 0) u /= 2, ++t;
    // 确定性基底集，适用于 n < 2^64
    long long bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (long long a : bases) {
        if (a % n == 0) continue;
        long long v = quickPow(a % n, u, n);
        if (v == 1) continue;
        int s = 0;
        for (; s < t; ++s) {
            if (v == n - 1) break;
            v = (__int128)v * v % n;
        }
        if (s == t) return false;
    }
    return true;
}

int main() {
    srand(time(0));
    long long n;
    cin >> n;
    cout << (millerRabin(n) ? "Yes" : "No") << endl;
    return 0;
}