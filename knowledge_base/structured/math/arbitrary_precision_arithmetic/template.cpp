#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct BigInt {
    vector<int> digits;
    bool sign; // true for negative
    static const int BASE = 1000000000;
    static const int BASE_DIGITS = 9;

    BigInt() : sign(false) {}
    BigInt(long long v) {
        *this = v;
    }
    BigInt(const string &s) {
        read(s);
    }

    void operator=(long long v) {
        sign = false;
        if (v < 0) sign = true, v = -v;
        digits.clear();
        for (; v > 0; v /= BASE)
            digits.push_back(v % BASE);
    }

    void read(const string &s) {
        sign = false;
        digits.clear();
        int pos = 0;
        if (s[pos] == '-') sign = true, ++pos;
        for (int i = s.size() - 1; i >= pos; i -= BASE_DIGITS) {
            int x = 0;
            for (int j = max(pos, i - BASE_DIGITS + 1); j <= i; ++j)
                x = x * 10 + s[j] - '0';
            digits.push_back(x);
        }
        trim();
    }

    void trim() {
        while (!digits.empty() && digits.back() == 0)
            digits.pop_back();
        if (digits.empty()) sign = false;
    }

    string str() const {
        if (digits.empty()) return "0";
        string res;
        if (sign) res += "-";
        res += to_string(digits.back());
        for (int i = (int)digits.size() - 2; i >= 0; --i) {
            string t = to_string(digits[i]);
            res += string(BASE_DIGITS - t.size(), '0') + t;
        }
        return res;
    }

    BigInt operator+(const BigInt &v) const {
        if (sign == v.sign) {
            BigInt res = v;
            int carry = 0;
            for (int i = 0; i < max(digits.size(), v.digits.size()) || carry; ++i) {
                if (i == res.digits.size()) res.digits.push_back(0);
                res.digits[i] += carry + (i < digits.size() ? digits[i] : 0);
                carry = res.digits[i] >= BASE;
                if (carry) res.digits[i] -= BASE;
            }
            return res;
        }
        return *this - (-v);
    }

    BigInt operator-(const BigInt &v) const {
        if (sign == v.sign) {
            if (abs() >= v.abs()) {
                BigInt res = *this;
                int carry = 0;
                for (int i = 0; i < v.digits.size() || carry; ++i) {
                    res.digits[i] -= carry + (i < v.digits.size() ? v.digits[i] : 0);
                    carry = res.digits[i] < 0;
                    if (carry) res.digits[i] += BASE;
                }
                res.trim();
                return res;
            }
            return -(v - *this);
        }
        return *this + (-v);
    }

    BigInt operator*(const BigInt &v) const {
        vector<long long> num(digits.size() + v.digits.size());
        for (int i = 0; i < digits.size(); ++i)
            for (int j = 0; j < v.digits.size(); ++j)
                num[i + j] += (long long)digits[i] * v.digits[j];
        long long carry = 0;
        for (int i = 0; i < num.size(); ++i) {
            num[i] += carry;
            carry = num[i] / BASE;
            num[i] %= BASE;
        }
        BigInt res;
        res.sign = sign ^ v.sign;
        res.digits.resize(num.size());
        for (int i = 0; i < num.size(); ++i)
            res.digits[i] = num[i];
        res.trim();
        return res;
    }

    BigInt operator/(const BigInt &v) const {
        return divmod(*this, v).first;
    }

    BigInt operator%(const BigInt &v) const {
        return divmod(*this, v).second;
    }

    static pair<BigInt, BigInt> divmod(const BigInt &a, const BigInt &b) {
        int norm = BASE / (b.digits.back() + 1);
        BigInt x = a.abs() * norm;
        BigInt y = b.abs() * norm;
        BigInt q, r;
        q.digits.resize(x.digits.size());
        for (int i = (int)x.digits.size() - 1; i >= 0; --i) {
            r = r * BASE + x.digits[i];
            int s1 = r.digits.size() <= y.digits.size() ? 0 : r.digits[y.digits.size()];
            int s2 = r.digits.size() <= y.digits.size() - 1 ? 0 : r.digits[y.digits.size() - 1];
            int d = (long long)BASE * s1 + s2;
            d /= y.digits.back();
            r = r - y * d;
            while (r.sign) r = r + y, --d;
            q.digits[i] = d;
        }
        q.sign = a.sign ^ b.sign;
        r.sign = a.sign;
        q.trim();
        r.trim();
        return {q, r / norm};
    }

    BigInt operator-() const {
        BigInt res = *this;
        res.sign = !sign;
        return res;
    }

    bool operator<(const BigInt &v) const {
        if (sign != v.sign) return sign;
        if (digits.size() != v.digits.size())
            return digits.size() < v.digits.size();
        for (int i = (int)digits.size() - 1; i >= 0; --i)
            if (digits[i] != v.digits[i])
                return digits[i] < v.digits[i];
        return false;
    }

    bool operator>=(const BigInt &v) const { return !(*this < v); }
    bool operator<=(const BigInt &v) const { return !(v < *this); }
    bool operator==(const BigInt &v) const { return !(*this < v) && !(v < *this); }

    BigInt abs() const {
        BigInt res = *this;
        res.sign = false;
        return res;
    }
};

int main() {
    // Example usage
    BigInt a("12345678901234567890");
    BigInt b("987654321");
    BigInt c = a + b;
    printf("%s\n", c.str().c_str());
    return 0;
}