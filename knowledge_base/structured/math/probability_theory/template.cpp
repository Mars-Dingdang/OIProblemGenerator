#include <bits/stdc++.h>
using namespace std;

// Example: Calculating expectation of a discrete random variable
// Given probabilities p[i] for values x[i]
double expectation_discrete(const vector<double>& x, const vector<double>& p) {
    double ex = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        ex += x[i] * p[i];
    }
    return ex;
}

// Example: Calculating variance using formula D(X) = E(X^2) - (E(X))^2
double variance_discrete(const vector<double>& x, const vector<double>& p) {
    double ex = 0.0, ex2 = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        ex += x[i] * p[i];
        ex2 += x[i] * x[i] * p[i];
    }
    return ex2 - ex * ex;
}

// Example: Covariance of two discrete random variables
double covariance_discrete(const vector<double>& x, const vector<double>& y, const vector<vector<double>>& joint_p) {
    double ex = 0.0, ey = 0.0, exy = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        for (size_t j = 0; j < y.size(); ++j) {
            ex += x[i] * joint_p[i][j];
            ey += y[j] * joint_p[i][j];
            exy += x[i] * y[j] * joint_p[i][j];
        }
    }
    return exy - ex * ey;
}

// Example: Solving expectation via indicator variables (as in text)
// For sequence where a_k = k with probability p_k, else 0
double expectation_indicator(const vector<double>& p) {
    double ex = 0.0;
    for (size_t k = 0; k < p.size(); ++k) {
        ex += (k + 1) * p[k]; // assuming indices start from 1
    }
    return ex;
}

int main() {
    // Example usage
    vector<double> values = {1.0, 2.0, 3.0};
    vector<double> probs = {0.2, 0.5, 0.3};
    cout << "Expectation: " << expectation_discrete(values, probs) << endl;
    cout << "Variance: " << variance_discrete(values, probs) << endl;
    return 0;
}