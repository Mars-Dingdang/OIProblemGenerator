#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Double hashing parameters
const int BASE1 = 91138233;
const int MOD1 = 972663749;
const int BASE2 = 97266353;
const int MOD2 = 1000000009;
const int MAXN = 2000;
const int ALPH = 26;

int n;
string A, B;

// Precomputed powers for up to 2*MAXN
ll pow1[2 * MAXN + 5];
ll pow2[2 * MAXN + 5];

// Prefix hashes for A and B
ll ha1[MAXN + 5], ha2[MAXN + 5];
ll hb1[MAXN + 5], hb2[MAXN + 5];

// next_pos[i][c] = smallest index j > i with B[j] == c, or n if none
int nxt_pos[MAXN + 5][ALPH];

// Bitset for efficient iteration over sets of positions
struct Bitset {
    static const int WORDS = (MAXN + 63) / 64;
    uint64_t bits[WORDS];
    int n; // actual size (0..n-1)

    Bitset(int size = 0) : n(size) {
        clear();
    }

    void clear() {
        memset(bits, 0, sizeof bits);
    }

    void set(int pos) {
        int w = pos >> 6;
        int b = pos & 63;
        bits[w] |= (1ULL << b);
    }

    void reset(int pos) {
        int w = pos >> 6;
        int b = pos & 63;
        bits[w] &= ~(1ULL << b);
    }

    bool test(int pos) const {
        int w = pos >> 6;
        int b = pos & 63;
        return (bits[w] >> b) & 1;
    }

    // Iterate over all set bits and call f(bit)
    template<typename F>
    void iterate(F f) const {
        for (int i = 0; i < WORDS; ++i) {
            uint64_t w = bits[i];
            while (w) {
                int offset = __builtin_ctzll(w);
                int bit = (i << 6) + offset;
                if (bit >= n) break;
                f(bit);
                w &= w - 1; // clear lowest set bit
            }
        }
    }
};

// Precompute powers for hashing
void init_pows(int max_len) {
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i <= max_len; ++i) {
        pow1[i] = pow1[i - 1] * BASE1 % MOD1;
        pow2[i] = pow2[i - 1] * BASE2 % MOD2;
    }
}

// Compute prefix hashes for a string
void compute_hashes(const string &s, ll h1[], ll h2[]) {
    int len = s.size();
    h1[0] = h2[0] = 0;
    for (int i = 0; i < len; ++i) {
        h1[i + 1] = (h1[i] * BASE1 + s[i]) % MOD1;
        h2[i + 1] = (h2[i] * BASE2 + s[i]) % MOD2;
    }
}

// Compute hash of substring s[l..r] (0-indexed) using precomputed prefix hashes
pair<ll, ll> substr_hash(ll h1[], ll h2[], int l, int r, ll pow1[], ll pow2[]) {
    int len = r - l + 1;
    ll hash1 = (h1[r + 1] - h1[l] * pow1[len] % MOD1 + MOD1) % MOD1;
    ll hash2 = (h2[r + 1] - h2[l] * pow2[len] % MOD2 + MOD2) % MOD2;
    return {hash1, hash2};
}

// Compute hash of suffix of B starting at pos (0-indexed)
pair<ll, ll> suffix_hash(int pos, ll pow1[], ll pow2[]) {
    if (pos >= n) return {0, 0};
    int len = n - pos;
    ll hash1 = (hb1[n] - hb1[pos] * pow1[len] % MOD1 + MOD1) % MOD1;
    ll hash2 = (hb2[n] - hb2[pos] * pow2[len] % MOD2 + MOD2) % MOD2;
    return {hash1, hash2};
}

void solve() {
    cin >> n >> A >> B;

    // Precompute powers up to 2*n
    init_pows(2 * n);

    // Compute hashes for A and B
    compute_hashes(A, ha1, ha2);
    compute_hashes(B, hb1, hb2);

    // Precompute next_pos for B
    vector<int> last(ALPH, n);
    for (int i = n - 1; i >= 0; --i) {
        for (int c = 0; c < ALPH; ++c) {
            nxt_pos[i][c] = last[c];
        }
        last[B[i] - 'a'] = i;
    }
    // For convenience, define next_pos for i = n as n (no further occurrence)
    for (int c = 0; c < ALPH; ++c) nxt_pos[n][c] = n;

    // Set to store distinct strings (as double hash)
    set<pair<ll, ll>> seen;

    // Process each starting index i in A
    for (int i = 0; i < n; ++i) {
        Bitset current(n);
        // Initialize current with positions where B has character A[i]
        for (int p = 0; p < n; ++p) {
            if (B[p] == A[i]) {
                current.set(p);
            }
        }

        // Extend substring A[i..j]
        for (int j = i; j < n; ++j) {
            int lenX = j - i + 1;
            // Process each possible ending position p in current bitset
            current.iterate([&](int p) {
                // Compute hash of X = A[i..j]
                auto hashX = substr_hash(ha1, ha2, i, j, pow1, pow2);
                // Compute hash of suffix Y = B[p+1 .. n-1]
                auto hashY = suffix_hash(p + 1, pow1, pow2);
                int lenY = n - (p + 1);
                // Combine hashes: hash(X+Y) = hashX * base^{lenY} + hashY
                ll comb1 = (hashX.first * pow1[lenY] % MOD1 + hashY.first) % MOD1;
                ll comb2 = (hashX.second * pow2[lenY] % MOD2 + hashY.second) % MOD2;
                seen.insert({comb1, comb2});
            });

            // If we can extend further, compute next bitset for character A[j+1]
            if (j + 1 < n) {
                Bitset next(n);
                char c = A[j + 1];
                current.iterate([&](int p) {
                    int q = nxt_pos[p][c - 'a'];
                    if (q < n) {
                        next.set(q);
                    }
                });
                current = next;
                // If no possible extension, break
                bool empty = true;
                for (int k = 0; k < Bitset::WORDS; ++k) {
                    if (current.bits[k]) { empty = false; break; }
                }
                if (empty) break;
            }
        }
    }

    cout << seen.size() << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}