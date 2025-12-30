#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    double norm() const { return hypot(x, y); }
    Point rotate(double theta) const {
        return Point(x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta));
    }
};

struct Circle {
    Point c;
    double r;
    Circle(Point c = Point(), double r = 0) : c(c), r(r) {}
};

// Returns intersection points of two circles.
// Returns empty vector if circles are separate or identical.
// Returns one point if tangent, two points if intersect.
vector<Point> circleCircleIntersection(Circle a, Circle b) {
    vector<Point> res;
    double d = (b.c - a.c).norm();
    if (d > a.r + b.r + EPS || d < fabs(a.r - b.r) - EPS || d < EPS) return res;
    double theta = acos((a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d));
    Point dir = (b.c - a.c) * (1.0 / d);
    Point p1 = a.c + dir.rotate(theta) * a.r;
    Point p2 = a.c + dir.rotate(-theta) * a.r;
    res.push_back(p1);
    if (fabs(d - a.r - b.r) > EPS && fabs(d - fabs(a.r - b.r)) > EPS) {
        res.push_back(p2);
    }
    return res;
}

int main() {
    // Example usage
    Circle c1(Point(0, 0), 5);
    Circle c2(Point(8, 0), 5);
    auto pts = circleCircleIntersection(c1, c2);
    for (auto& p : pts) {
        cout << fixed << setprecision(6) << p.x << ' ' << p.y << endl;
    }
    return 0;
}