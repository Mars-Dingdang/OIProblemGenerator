struct Gaussian {
    long long a, b; // a + bi

    Gaussian(long long a = 0, long long b = 0) : a(a), b(b) {}

    long long norm() const { return a * a + b * b; }

    bool operator==(const Gaussian& o) const { return a == o.a && b == o.b; }
    bool operator!=(const Gaussian& o) const { return !(*this == o); }
};

// 返回离实数 x 最近的整数（四舍五入）
long long round_div(long long x, long long d) {
    return (x + (d > 0 ? d/2 : -d/2)) / d;
}

// 高斯整数带余除法：返回 gamma = beta - eta * alpha
Gaussian gaussian_mod(const Gaussian& alpha, const Gaussian& beta) {
    // 计算 (beta / alpha) = (beta * conj(alpha)) / N(alpha)
    long long na = alpha.norm();
    long long real_part = beta.a * alpha.a + beta.b * alpha.b; // Re(beta * conj(alpha))
    long long imag_part = beta.b * alpha.a - beta.a * alpha.b; // Im(beta * conj(alpha))

    // 四舍五入得到最接近的高斯整数商
    long long qr = round_div(real_part, na);
    long long qi = round_div(imag_part, na);

    Gaussian eta(qr, qi);
    Gaussian product(eta.a * alpha.a - eta.b * alpha.b,
                    eta.a * alpha.b + eta.b * alpha.a);
    return Gaussian(beta.a - product.a, beta.b - product.b);
}

// 高斯整数 GCD
Gaussian gcd(Gaussian alpha, Gaussian beta) {
    while (beta.a != 0 || beta.b != 0) {
        auto gamma = gaussian_mod(alpha, beta);
        alpha = beta;
        beta = gamma;
    }
    return alpha;
}

// 示例：如何使用
/*
int main() {
    Gaussian x(1, 2); // 1 + 2i
    Gaussian y(3, 1); // 3 + i
    Gaussian g = gcd(x, y);
    // 输出 g 即为所求的最小模长生成元（在相伴意义下）
    cout << g.a << " + " << g.b << "i" << endl;
    return 0;
}
*/