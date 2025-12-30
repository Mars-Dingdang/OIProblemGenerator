#include <iostream>
#include <cmath>

const double PI = acos(-1.0);

// 角度转弧度
double deg2rad(double deg) {
    return deg * PI / 180.0;
}

// 弧度转角度
double rad2deg(double rad) {
    return rad * 180.0 / PI;
}

// 直角坐标转极坐标 (ρ, φ)
std::pair<double, double> cartesian2polar(double x, double y) {
    double rho = sqrt(x * x + y * y);
    double phi = atan2(y, x); // 使用 atan2 自动处理象限
    return {rho, phi};
}

// 极坐标转直角坐标
std::pair<double, double> polar2cartesian(double rho, double phi) {
    double x = rho * cos(phi);
    double y = rho * sin(phi);
    return {x, y};
}

// 球坐标转直角坐标 (r, θ, φ) -> (x, y, z)
// 约定：θ 为天顶角（与 z 轴夹角），φ 为方位角（在 xy 平面内与 x 轴夹角）
std::tuple<double, double, double> spherical2cartesian(double r, double theta, double phi) {
    double x = r * sin(theta) * cos(phi);
    double y = r * sin(theta) * sin(phi);
    double z = r * cos(theta);
    return {x, y, z};
}

// 直角坐标转球坐标
std::tuple<double, double, double> cartesian2spherical(double x, double y, double z) {
    double r = sqrt(x * x + y * y + z * z);
    double theta = acos(z / r); // 天顶角
    double phi = atan2(y, x);   // 方位角
    return {r, theta, phi};
}

int main() {
    // 示例用法
    double deg = 45.0;
    double rad = deg2rad(deg);
    std::cout << "45 degrees = " << rad << " radians" << std::endl;
    
    double x = 1.0, y = 1.0;
    auto [rho, phi] = cartesian2polar(x, y);
    std::cout << "Cartesian (" << x << ", " << y << ") -> Polar (rho=" << rho << ", phi=" << phi << ")" << std::endl;
    
    return 0;
}