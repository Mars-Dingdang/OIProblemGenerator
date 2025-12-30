#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

const double INITIAL_TEMPERATURE = 1000.0;
const double COOLING_RATE = 0.995;
const double EPSILON = 1e-8;

// 示例：n维空间中最小化到各点带权距离和
double evaluate(const std::vector<double>& pos, const std::vector<int>& x, const std::vector<int>& y, const std::vector<int>& w) {
    double res = 0;
    for (int i = 0; i < x.size(); ++i) {
        double dx = x[i] - pos[0], dy = y[i] - pos[1];
        double dist = std::sqrt(dx * dx + dy * dy);
        res += dist * w[i];
    }
    return res;
}

void hill_climb(std::vector<double>& ans, const std::vector<int>& x, const std::vector<int>& y, const std::vector<int>& w) {
    double t = INITIAL_TEMPERATURE;
    while (t > EPSILON) {
        std::vector<double> grad(2, 0);
        for (int i = 0; i < x.size(); ++i) {
            double dx = x[i] - ans[0], dy = y[i] - ans[1];
            double dist = std::sqrt(dx * dx + dy * dy + 1e-8); // 防除零
            grad[0] += (dx / dist) * w[i];
            grad[1] += (dy / dist) * w[i];
        }
        ans[0] += grad[0] * t;
        ans[1] += grad[1] * t;
        t *= COOLING_RATE;
    }
}

int main() {
    int n; std::cin >> n;
    std::vector<int> x(n), y(n), w(n);
    std::vector<double> ans(2, 0);
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i] >> y[i] >> w[i];
        ans[0] += x[i]; ans[1] += y[i];
    }
    ans[0] /= n; ans[1] /= n;
    hill_climb(ans, x, y, w);
    std::cout << std::fixed << std::setprecision(3) << ans[0] << ' ' << ans[1] << '\n';
    return 0;
}