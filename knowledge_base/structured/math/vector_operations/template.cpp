#include <bits/stdc++.h>
using namespace std;

struct Vec3 {
    double x, y, z;
    Vec3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    Vec3 operator+(const Vec3& o) const { return Vec3(x + o.x, y + o.y, z + o.z); }
    Vec3 operator-(const Vec3& o) const { return Vec3(x - o.x, y - o.y, z - o.z); }
    Vec3 operator*(double k) const { return Vec3(x * k, y * k, z * k); }
    double dot(const Vec3& o) const { return x * o.x + y * o.y + z * o.z; }
    Vec3 cross(const Vec3& o) const {
        return Vec3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }
    double norm() const { return sqrt(dot(*this)); }
    Vec3 unit() const { double n = norm(); return n > 0 ? (*this) * (1.0 / n) : *this; }
};

// 绕轴旋转 (axis u 为单位向量, theta 为弧度)
Vec3 rotate_axis(const Vec3& v, const Vec3& u, double theta) {
    double ct = cos(theta), st = sin(theta);
    double ux = u.x, uy = u.y, uz = u.z;
    double a = v.x * (ux * ux * (1 - ct) + ct) +
               v.y * (ux * uy * (1 - ct) - uz * st) +
               v.z * (ux * uz * (1 - ct) + uy * st);
    double b = v.x * (ux * uy * (1 - ct) + uz * st) +
               v.y * (uy * uy * (1 - ct) + ct) +
               v.z * (uy * uz * (1 - ct) - ux * st);
    double c = v.x * (ux * uz * (1 - ct) - uy * st) +
               v.y * (uy * uz * (1 - ct) + ux * st) +
               v.z * (uz * uz * (1 - ct) + ct);
    return Vec3(a, b, c);
}

// 二维向量叉积 (返回标量)
double cross2d(const Vec3& a, const Vec3& b) {
    return a.x * b.y - a.y * b.x;
}

// 混合积 (三重积)
double scalar_triple(const Vec3& a, const Vec3& b, const Vec3& c) {
    return a.dot(b.cross(c));
}

int main() {
    // 示例用法
    Vec3 a(1, 0, 0), b(0, 1, 0);
    cout << "Dot: " << a.dot(b) << endl;          // 0
    Vec3 c = a.cross(b);
    cout << "Cross: (" << c.x << ", " << c.y << ", " << c.z << ")" << endl; // (0,0,1)
    Vec3 axis(0, 0, 1);
    Vec3 r = rotate_axis(a, axis, M_PI / 2);
    cout << "Rotated: (" << r.x << ", " << r.y << ", " << r.z << ")" << endl; // (0,1,0)
    return 0;
}