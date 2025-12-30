template <int MOD>
struct ModInt {
    int v;
    ModInt() : v(0) {}
    ModInt(long long _v) : v(int(_v % MOD)) { if (v < 0) v += MOD; }
    ModInt operator+(ModInt o) const { int res = v + o.v; if (res >= MOD) res -= MOD; return ModInt(res); }
    ModInt operator-(ModInt o) const { int res = v - o.v; if (res < 0) res += MOD; return ModInt(res); }
    ModInt operator*(ModInt o) const { return ModInt(1LL * v * o.v % MOD); }
    ModInt pow(long long b) const {
        ModInt res(1), a = *this;
        while (b) {
            if (b & 1) res = res * a;
            a = a * a;
            b >>= 1;
        }
        return res;
    }
    ModInt inv() const { return pow(MOD - 2); } // MOD must be prime
    ModInt operator/(ModInt o) const { return *this * o.inv(); }
    bool operator==(ModInt o) const { return v == o.v; }
    friend std::ostream& operator<<(std::ostream& os, ModInt m) { return os << m.v; }
};