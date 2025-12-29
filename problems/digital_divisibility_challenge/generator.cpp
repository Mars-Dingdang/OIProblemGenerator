#include <iostream>
#include <random>
#include <chrono>
#include <string>

int main() {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> n_dist(1, 100000);
    int n = n_dist(rng);
    
    std::string s;
    s.reserve(n);
    std::uniform_int_distribution<int> digit_dist(0, 9);
    for (int i = 0; i < n; ++i) {
        s += ('0' + digit_dist(rng));
    }
    
    std::cout << n << '\n' << s << std::endl;
    return 0;
}