#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

// Euclidean distance in n-dimensional space
double euclidean_distance(const vector<double>& a, const vector<double>& b) {
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        double diff = a[i] - b[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

// Manhattan distance in n-dimensional space
double manhattan_distance(const vector<double>& a, const vector<double>& b) {
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += fabs(a[i] - b[i]);
    }
    return sum;
}

// Chebyshev distance in n-dimensional space
double chebyshev_distance(const vector<double>& a, const vector<double>& b) {
    double max_diff = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        max_diff = max(max_diff, fabs(a[i] - b[i]));
    }
    return max_diff;
}

// Convert point for Manhattan-Chebyshev transformation
pair<double, double> transform_manhattan_to_chebyshev(double x, double y) {
    return {x + y, x - y};
}

pair<double, double> transform_chebyshev_to_manhattan(double x, double y) {
    return {(x + y) / 2.0, (x - y) / 2.0};
}