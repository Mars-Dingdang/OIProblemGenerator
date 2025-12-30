// Extended Euclidean algorithm for modular inverse (works for any coprime a, m)
void ex_gcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1;
        y = 0;
    } else {
        ex_gcd(b, a % b, y, x);
        y -= a / b * x;
    }
}

int inverse(int a, int m) {
    int x, y;
    ex_gcd(a, m, x, y);
    return (x % m + m) % m;
}

// Fast exponentiation inverse (only for prime modulus)
int pow(int a, int b, int m) {
    long long res = 1, po = a;
    for (; b; b >>= 1) {
        if (b & 1) res = res * po % m;
        po = po * po % m;
    }
    return res;
}

int inverse_prime(int a, int p) {
    return pow(a, p - 2, p);
}

// Batch inverse for array a modulo m (all elements must be coprime with m)
vector<int> batch_inverse(const vector<int>& a, int m) {
    int n = a.size();
    vector<int> prod(n);
    long long s = 1;
    for (int i = 0; i < n; ++i) {
        prod[i] = s;
        s = s * a[i] % m;
    }
    s = inverse(s, m);
    vector<int> res(n);
    for (int i = n - 1; i >= 0; --i) {
        res[i] = s * prod[i] % m;
        s = s * a[i] % m;
    }
    return res;
}

// Linear preprocessing of inverses 1..n modulo prime p
vector<int> precompute_inverses(int n, int p) {
    vector<int> inv(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = (long long)(p - p / i) * inv[p % i] % p;
    }
    return inv;
}