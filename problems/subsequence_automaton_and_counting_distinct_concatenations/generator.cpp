#include <bits/stdc++.h>
using namespace std;

int main() {
    // Random number generator with time-based seed
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    // Generate exactly one test case
    int T = 1;
    // Random n between 1 and 2000 (inclusive)
    int n = uniform_int_distribution<int>(1, 2000)(rng);
    
    // Generate two random strings of length n
    string A, B;
    for (int i = 0; i < n; ++i) {
        A.push_back(uniform_int_distribution<char>('a', 'z')(rng));
        B.push_back(uniform_int_distribution<char>('a', 'z')(rng));
    }
    
    // Output the test case
    cout << T << endl;
    cout << n << endl;
    cout << A << endl;
    cout << B << endl;
    
    return 0;
}