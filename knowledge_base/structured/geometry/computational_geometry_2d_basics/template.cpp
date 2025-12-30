#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);

int sgn(double x) {
    if (fabs(x) < EPS) return 0;
    return x < 0 ? -1 : 1;
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator+(const Point& b) const { return Point(x + b.x, y + b.y); }
    Point operator-(const Point& b) const { return Point(x - b.x, y - b.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    Point operator/(double k) const { return Point(x / k, y / k); }
    bool operator==(const Point& b) const { return sgn(x - b.x) == 0 && sgn(y - b.y) == 0; }
    double dot(const Point& b) const { return x * b.x + y * b.y; }
    double cross(const Point& b) const { return x * b.y - y * b.x; }
    double len() const { return hypot(x, y); }
    double len2() const { return x * x + y * y; }
    Point rotate(double rad) const { return Point(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)); }
    Point unit() const { double l = len(); return Point(x / l, y / l); }
};

typedef Point Vector;

struct Line {
    Point p;
    Vector v;
    Line(Point p = Point(), Vector v = Vector()) : p(p), v(v) {}
    Line(Point a, Point b) : p(a), v(b - a) {}
};

struct Segment {
    Point a, b;
    Segment(Point a = Point(), Point b = Point()) : a(a), b(b) {}
};

struct Circle {
    Point c;
    double r;
    Circle(Point c = Point(), double r = 0) : c(c), r(r) {}
};

// Point-line relation: -1 right, 0 on, 1 left
int point_line_relation(Point p, Line l) {
    return sgn(l.v.cross(p - l.p));
}

// Quick rejection and straddling test for segment intersection
bool segment_intersection(Segment s1, Segment s2) {
    if (max(s1.a.x, s1.b.x) < min(s2.a.x, s2.b.x) ||
        max(s2.a.x, s2.b.x) < min(s1.a.x, s1.b.x) ||
        max(s1.a.y, s1.b.y) < min(s2.a.y, s2.b.y) ||
        max(s2.a.y, s2.b.y) < min(s1.a.y, s1.b.y)) return false;
    int d1 = sgn((s2.a - s1.a).cross(s1.b - s1.a));
    int d2 = sgn((s2.b - s1.a).cross(s1.b - s1.a));
    int d3 = sgn((s1.a - s2.a).cross(s2.b - s2.a));
    int d4 = sgn((s1.b - s2.a).cross(s2.b - s2.a));
    if (d1 * d2 < 0 && d3 * d4 < 0) return true;
    if (d1 == 0 && sgn((s2.a - s1.a).dot(s2.a - s1.b)) <= 0) return true;
    if (d2 == 0 && sgn((s2.b - s1.a).dot(s2.b - s1.b)) <= 0) return true;
    if (d3 == 0 && sgn((s1.a - s2.a).dot(s1.a - s2.b)) <= 0) return true;
    if (d4 == 0 && sgn((s1.b - s2.a).dot(s1.b - s2.b)) <= 0) return true;
    return false;
}

// Ray casting algorithm for point in polygon
bool point_in_polygon(Point p, const vector<Point>& poly) {
    int n = poly.size();
    if (n < 3) return false;
    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if ((poly[i].y > p.y) != (poly[j].y > p.y) &&
            p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x)
            inside = !inside;
    }
    return inside;
}

// Area of polygon (signed)
double polygon_area(const vector<Point>& poly) {
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        area += poly[i].cross(poly[(i + 1) % n]);
    }
    return fabs(area) / 2;
}

// Perimeter of polygon
double polygon_perimeter(const vector<Point>& poly) {
    double peri = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        peri += (poly[(i + 1) % n] - poly[i]).len();
    }
    return peri;
}

// Line intersection
Point line_intersection(Line l1, Line l2) {
    Vector u = l1.p - l2.p;
    double t = l2.v.cross(u) / l1.v.cross(l2.v);
    return l1.p + l1.v * t;
}

// Circle-line intersection
vector<Point> circle_line_intersection(Circle c, Line l) {
    vector<Point> res;
    Vector v = l.v.unit();
    Point p = l.p;
    double a = v.dot(v);
    double b = 2 * v.dot(p - c.c);
    double cc = (p - c.c).dot(p - c.c) - c.r * c.r;
    double delta = b * b - 4 * a * cc;
    if (sgn(delta) < 0) return res;
    if (sgn(delta) == 0) {
        double t = -b / (2 * a);
        res.push_back(p + v * t);
    } else {
        double t1 = (-b - sqrt(delta)) / (2 * a);
        double t2 = (-b + sqrt(delta)) / (2 * a);
        res.push_back(p + v * t1);
        res.push_back(p + v * t2);
    }
    return res;
}

// Circle-circle intersection
vector<Point> circle_circle_intersection(Circle c1, Circle c2) {
    vector<Point> res;
    double d = (c1.c - c2.c).len();
    if (sgn(d) == 0 || sgn(d - (c1.r + c2.r)) > 0 || sgn(fabs(c1.r - c2.r) - d) > 0) return res;
    double a = (c1.r * c1.r - c2.r * c2.r + d * d) / (2 * d);
    double h = sqrt(c1.r * c1.r - a * a);
    Point p = c1.c + (c2.c - c1.c).unit() * a;
    Vector v = (c2.c - c1.c).unit().rotate(PI / 2) * h;
    res.push_back(p + v);
    res.push_back(p - v);
    return res;
}