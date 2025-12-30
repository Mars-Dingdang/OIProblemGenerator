#include <vector>
#include <string>
#include <iostream>

// Brute Force (BF) algorithm for string matching
// Returns all starting positions of pattern t in text s
std::vector<int> brute_force_match(const std::string& s, const std::string& t) {
    std::vector<int> ans;
    int n = s.length();
    int m = t.length();
    
    if (m == 0 || n < m) return ans;
    
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && s[i + j] == t[j]) {
            j++;
        }
        if (j == m) {
            ans.push_back(i);
        }
    }
    return ans;
}

// Example usage
int main() {
    std::string text = "ababcabcabababd";
    std::string pattern = "ababd";
    
    std::vector<int> positions = brute_force_match(text, pattern);
    
    std::cout << "Pattern found at positions: ";
    for (int pos : positions) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;
    
    return 0;
}