typedef long long LL;

// Extended Euclidean Algorithm
void exgcd(LL a, LL b, LL &x, LL &y) {
    if (b == 0) {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}

// Chinese Remainder Theorem (standard version)
// k: number of equations
// a[]: remainders a_i
// r[]: moduli n_i (must be pairwise coprime)
LL CRT(int k, LL a[], LL r[]) {
    LL n = 1, ans = 0;
    for (int i = 0; i < k; i++) n *= r[i];
    for (int i = 0; i < k; i++) {
        LL m = n / r[i];
        LL b, y;
        exgcd(m, r[i], b, y); // b is modular inverse of m modulo r[i]
        ans = (ans + a[i] * m % n * b % n) % n;
    }
    return (ans % n + n) % n;
}