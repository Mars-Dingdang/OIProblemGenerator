// Example: Finite field extension GF(p^n) implementation
#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353; // prime modulus
const int ROOT = 3;        // primitive root for NTT

// Polynomial operations in GF(p)
vector<int> poly_add(const vector<int>& a, const vector<int>& b) {
    vector<int> res(max(a.size(), b.size()));
    for (int i = 0; i < (int)a.size(); i++) res[i] = (res[i] + a[i]) % MOD;
    for (int i = 0; i < (int)b.size(); i++) res[i] = (res[i] + b[i]) % MOD;
    return res;
}

vector<int> poly_mul(const vector<int>& a, const vector<int>& b) {
    vector<int> res(a.size() + b.size() - 1, 0);
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = 0; j < (int)b.size(); j++)
            res[i + j] = (res[i + j] + 1LL * a[i] * b[j]) % MOD;
    return res;
}

// Modular inverse using extended Euclidean algorithm
int mod_inv(int a, int m = MOD) {
    int m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        int q = a / m;
        int t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

// Polynomial modulo operation (naive O(n^2))
vector<int> poly_mod(const vector<int>& a, const vector<int>& f) {
    vector<int> r = a;
    int n = f.size() - 1; // degree of f
    while ((int)r.size() >= f.size()) {
        int coef = r.back();
        int shift = r.size() - f.size();
        for (int i = 0; i < (int)f.size(); i++) {
            r[i + shift] = (r[i + shift] - 1LL * coef * f[i] % MOD + MOD) % MOD;
        }
        while (!r.empty() && r.back() == 0) r.pop_back();
    }
    return r;
}

// Element in extension field GF(p)[x]/(f(x))
struct ExtensionElement {
    vector<int> coeff; // coefficients in basis {1, alpha, alpha^2, ..., alpha^{n-1}}
    vector<int> mod_poly; // irreducible polynomial f(x)
    
    ExtensionElement(const vector<int>& c, const vector<int>& f) : coeff(c), mod_poly(f) {
        // Ensure degree < n
        coeff = poly_mod(coeff, mod_poly);
    }
    
    ExtensionElement operator+(const ExtensionElement& other) const {
        vector<int> res_coeff(max(coeff.size(), other.coeff.size()), 0);
        for (int i = 0; i < (int)coeff.size(); i++) res_coeff[i] = (res_coeff[i] + coeff[i]) % MOD;
        for (int i = 0; i < (int)other.coeff.size(); i++) res_coeff[i] = (res_coeff[i] + other.coeff[i]) % MOD;
        return ExtensionElement(res_coeff, mod_poly);
    }
    
    ExtensionElement operator*(const ExtensionElement& other) const {
        vector<int> prod = poly_mul(coeff, other.coeff);
        return ExtensionElement(prod, mod_poly);
    }
    
    // Multiplicative inverse using extended Euclidean algorithm for polynomials
    ExtensionElement inv() const {
        // Find polynomials u, v such that u*coeff + v*mod_poly = 1
        // Then u is the inverse
        vector<int> a = coeff;
        vector<int> b = mod_poly;
        vector<int> u = {1}, v = {0};
        vector<int> u1 = {0}, v1 = {1};
        
        while (!b.empty() && b.back() == 0) b.pop_back();
        while (!a.empty() && a.back() == 0) a.pop_back();
        
        while (!b.empty() && b.size() > 1) {
            // Polynomial division
            int deg_diff = a.size() - b.size();
            if (deg_diff < 0) break;
            
            int lead_inv = mod_inv(b.back());
            int factor = 1LL * a.back() * lead_inv % MOD;
            
            // Subtract factor * x^{deg_diff} * b from a
            vector<int> sub = b;
            sub.resize(b.size() + deg_diff, 0);
            for (int i = 0; i < deg_diff; i++) sub[i] = 0;
            for (int i = 0; i < (int)b.size(); i++) {
                sub[i + deg_diff] = 1LL * b[i] * factor % MOD;
            }
            
            for (int i = 0; i < (int)a.size(); i++) {
                a[i] = (a[i] - sub[i] + MOD) % MOD;
            }
            while (!a.empty() && a.back() == 0) a.pop_back();
            
            // Update u, v
            vector<int> u_sub = poly_mul({factor}, u1);
            u_sub.resize(u_sub.size() + deg_diff, 0);
            for (int i = 0; i < deg_diff; i++) u_sub[i] = 0;
            for (int i = 0; i < (int)u.size(); i++) {
                u[i] = (u[i] - u_sub[i] + MOD) % MOD;
            }
            while (!u.empty() && u.back() == 0) u.pop_back();
            
            swap(a, b);
            swap(u, u1);
            swap(v, v1);
        }
        
        // Now b should be constant
        if (b.empty() || b[0] == 0) {
            // No inverse
            return ExtensionElement({0}, mod_poly);
        }
        
        int scale = mod_inv(b[0]);
        for (int& x : u) x = 1LL * x * scale % MOD;
        return ExtensionElement(u, mod_poly);
    }
    
    void print() const {
        cout << "[";
        for (int i = 0; i < (int)coeff.size(); i++) {
            if (i > 0) cout << ", ";
            cout << coeff[i];
        }
        cout << "]";
    }
};

int main() {
    // Example: GF(2^2) with irreducible polynomial x^2 + x + 1
    vector<int> mod_poly = {1, 1, 1}; // x^2 + x + 1
    
    // Elements in GF(4): 0, 1, α, α+1
    ExtensionElement a({1, 0}, mod_poly); // 1
    ExtensionElement b({0, 1}, mod_poly); // α
    ExtensionElement c({1, 1}, mod_poly); // α+1
    
    cout << "Testing GF(4):\n";
    cout << "α * (α+1) = ";
    (b * c).print();
    cout << endl;
    
    cout << "(α+1) * (α+1) = ";
    (c * c).print();
    cout << endl;
    
    cout << "1/α = ";
    b.inv().print();
    cout << endl;
    
    return 0;
}