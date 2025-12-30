#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> cd;

// Basic operations
cd add(cd a, cd b) { return a + b; }
cd sub(cd a, cd b) { return a - b; }
cd mul(cd a, cd b) { return a * b; }
cd div(cd a, cd b) { return a / b; }

// Polar form conversions
cd polar_to_complex(double r, double theta) {
    return polar(r, theta);
}
pair<double, double> complex_to_polar(cd z) {
    return {abs(z), arg(z)};
}

// Spherical to Cartesian coordinates (using complex for 2D projection)
void spherical_to_cartesian(double r, double theta, double phi, double &x, double &y, double &z) {
    x = r * sin(theta) * cos(phi);
    y = r * sin(theta) * sin(phi);
    z = r * cos(theta);
}

// Cartesian to spherical coordinates
void cartesian_to_spherical(double x, double y, double z, double &r, double &theta, double &phi) {
    r = sqrt(x*x + y*y + z*z);
    theta = acos(z / r);
    phi = atan2(y, x);
}

// Roots of unity (for FFT)
vector<cd> roots_of_unity(int n) {
    vector<cd> roots(n);
    double angle = 2 * M_PI / n;
    for (int i = 0; i < n; ++i) {
        roots[i] = cd(cos(angle * i), sin(angle * i));
    }
    return roots;
}