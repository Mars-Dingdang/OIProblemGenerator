// Calculate (n!)_p mod p (prime modulus)
int factmod_prime(int n, int p) {
    vector<int> f(p);
    f[0] = 1;
    for (int i = 1; i < p; ++i)
        f[i] = (long long)f[i - 1] * i % p;
    int res = 1;
    while (n > 1) {
        if ((n / p) & 1) res = p - res;
        res = (long long)res * f[n % p] % p;
        n /= p;
    }
    return res;
}

// Calculate (n!)_p mod p^α (prime power modulus)
int factmod_prime_power(int n, int p, int pa) {
    vector<int> f(pa);
    f[0] = 1;
    for (int i = 1; i < pa; ++i)
        f[i] = (i % p) ? (long long)f[i - 1] * i % pa : f[i - 1];
    bool neg = (p != 2 || pa <= 4); // ±1 sign: -1 unless p=2 and α≥3
    int res = 1;
    while (n > 1) {
        if ((n / pa) & neg) res = pa - res;
        res = (long long)res * f[n % pa] % pa;
        n /= p;
    }
    return res;
}

// Legendre formula: multiplicity of p in n!
int multiplicity_factorial(int n, int p) {
    int cnt = 0;
    do {
        n /= p;
        cnt += n;
    } while (n);
    return cnt;
}