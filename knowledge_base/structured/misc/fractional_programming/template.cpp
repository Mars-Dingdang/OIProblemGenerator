#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const double eps = 1e-6;

// Example: Maximize (sum a_i) / (sum b_i) over selected items
// with exactly k items chosen.

int n, k;
double a[100010], b[100010], c[100010];

bool check(double mid) {
    for (int i = 0; i < n; ++i)
        c[i] = a[i] - mid * b[i];
    sort(c, c + n, greater<double>());
    double sum = 0;
    for (int i = 0; i < k; ++i)
        sum += c[i];
    return sum >= 0;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) scanf("%lf", &a[i]);
    for (int i = 0; i < n; ++i) scanf("%lf", &b[i]);

    double L = 0, R = 1e6;
    while (R - L > eps) {
        double mid = (L + R) / 2;
        if (check(mid))
            L = mid;
        else
            R = mid;
    }
    printf("%.6f\n", L);
    return 0;
}