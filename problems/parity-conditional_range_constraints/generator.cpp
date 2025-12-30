#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist_nm(1, 100000);
    int n = dist_nm(rng);
    int m = dist_nm(rng);
    
    cout << n << " " << m << "\n";
    
    uniform_int_distribution<int> dist_type(0, 1);
    uniform_int_distribution<int> dist_j(1, n);
    
    for (int i = 0; i < m; i++) {
        uniform_int_distribution<int> dist_l(1, n);
        int l = dist_l(rng);
        uniform_int_distribution<int> dist_r(l, n);
        int r = dist_r(rng);
        int type = dist_type(rng);
        int j = dist_j(rng);
        
        cout << type << " " << l << " " << r << " " << j << "\n";
    }
    
    return 0;
}