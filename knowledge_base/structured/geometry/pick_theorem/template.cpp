#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

long long cross(const Point &a, const Point &b) {
    return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

// Returns: {area * 2, boundary_points, interior_points}
tuple<long long, long long, long long> pick_theorem(const vector<Point> &polygon) {
    int n = polygon.size();
    long long area2 = 0;
    long long boundary = 0;
    
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area2 += cross(polygon[i], polygon[j]);
        
        int dx = abs(polygon[j].x - polygon[i].x);
        int dy = abs(polygon[j].y - polygon[i].y);
        boundary += gcd(dx, dy);
    }
    
    area2 = abs(area2);
    long long interior = (area2 - boundary + 2) / 2;
    
    return {area2, boundary, interior};
}

int main() {
    // Example usage
    vector<Point> polygon = {{0, 0}, {4, 0}, {4, 3}, {0, 3}}; // Rectangle
    
    auto [area2, boundary, interior] = pick_theorem(polygon);
    
    cout << "Area: " << area2 / 2.0 << endl;
    cout << "Boundary points: " << boundary << endl;
    cout << "Interior points: " << interior << endl;
    
    return 0;
}