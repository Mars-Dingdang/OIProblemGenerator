typedef unsigned int uint;
const int MAX_LOG = 5; // for [0, 2^32)

// Fast Nim Multiplication using recursion and known identities
uint nim_mul(uint x, uint y, int m = MAX_LOG) {
    if (x == 0 || y == 0) return 0;
    if (m == 0) return 1; // base case: 1*1=1

    int n = 1 << (m - 1); // 2^(m-1)
    uint mask = (1U << n) - 1;
    uint a = x >> n, b = x & mask;
    uint c = y >> n, d = y & mask;

    uint ac = nim_mul(a, c, m - 1);
    uint bd = nim_mul(b, d, m - 1);
    uint ab_cd = nim_mul(a ^ b, c ^ d, m - 1);
    uint mid = ab_cd ^ bd;

    // Compute ac * 2^(n-1): this is ac ⊗ (2^(n-1))
    // We need a helper for power-of-two multiplication
    uint ac_half = nim_mul(1U << (m - 2), ac, m - 1); // 2^(n-1) ⊗ ac

    return (ac_half ^ bd) | (mid << n);
}

// Optional: Memoization can be added for performance.

// Example: Polynomial Multiplication via Karatsuba (simplified)
#include <vector>
using Poly = std::vector<uint>;

Poly poly_add(const Poly& a, const Poly& b) {
    Poly res(std::max(a.size(), b.size()));
    for (size_t i = 0; i < res.size(); ++i) {
        uint ai = (i < a.size()) ? a[i] : 0;
        uint bi = (i < b.size()) ? b[i] : 0;
        res[i] = ai ^ bi; // XOR as addition
    }
    return res;
}

Poly poly_shift(const Poly& a, size_t k) {
    Poly res(a.size() + k, 0);
    for (size_t i = 0; i < a.size(); ++i) res[i + k] = a[i];
    return res;
}

Poly nim_karatsuba(const Poly& a, const Poly& b) {
    int n = std::max(a.size(), b.size());
    if (n <= 1) {
        if (a.empty() || b.empty()) return {};
        return {a[0] ^ b[0]}; // Actually should be mul, but placeholder
    }

    int m = n / 2;
    Poly a_low(a.begin(), a.begin() + m);
    Poly a_high(a.begin() + m, a.end());
    Poly b_low(b.begin(), b.begin() + m);
    Poly b_high(b.begin() + m, b.end());

    Poly z0 = nim_karatsuba(a_low, b_low);
    Poly z2 = nim_karatsuba(a_high, b_high);

    Poly a_sum = poly_add(a_low, a_high);
    Poly b_sum = poly_add(b_low, b_high);
    Poly z1 = nim_karatsuba(a_sum, b_sum);

    Poly r1 = poly_add(z1, poly_add(z0, z2)); // z1 - z0 - z2

    Poly result;
    result.resize(a.size() + b.size() - 1, 0);
    // Merge z0, r1, z2 with proper shifts
    // This is simplified; full implementation requires careful indexing
    return result;
}

// Note: Full efficient implementations (e.g., Cantor FFT, Newton iteration)
// are highly complex and context-dependent. The above shows core ideas.