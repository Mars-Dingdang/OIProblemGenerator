#include <iostream>
#include <random>
#include <chrono>
#include <string>

int main() {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    
    std::uniform_int_distribution<int> n_dist(1, 200000);
    int n = n_dist(gen);
    
    std::cout << n << '\n';
    
    std::string s;
    s.reserve(n);
    std::uniform_int_distribution<int> char_dist(0, 1);
    for (int i = 0; i < n; ++i) {
        s += (char_dist(gen) ? '1' : '0');
    }
    
    std::cout << s << '\n';
    
    return 0;
}