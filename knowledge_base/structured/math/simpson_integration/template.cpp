// 普通辛普森法（固定分段数）
const int N = 1000000; // 分段数，根据精度要求调整
double f(double x) {
    // 定义被积函数
    return ...;
}

double simpson_integration(double a, double b) {
    double h = (b - a) / N;
    double s = f(a) + f(b);
    for (int i = 1; i <= N - 1; ++i) {
        double x = a + h * i;
        s += f(x) * ((i & 1) ? 4 : 2);
    }
    s *= h / 3;
    return s;
}

// 自适应辛普森法（推荐）
double simpson(double l, double r) {
    double mid = (l + r) / 2;
    return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;
}

double asr(double l, double r, double eps, double ans, int step) {
    double mid = (l + r) / 2;
    double fl = simpson(l, mid), fr = simpson(mid, r);
    if (abs(fl + fr - ans) <= 15 * eps && step < 0)
        return fl + fr + (fl + fr - ans) / 15;
    return asr(l, mid, eps / 2, fl, step - 1) + asr(mid, r, eps / 2, fr, step - 1);
}

double adaptive_simpson(double l, double r, double eps) {
    return asr(l, r, eps, simpson(l, r), 12); // 12 是最小递归深度，可调
}