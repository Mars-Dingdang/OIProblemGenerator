std::vector<std::string> duval(const std::string& s) {
    int n = s.length();
    std::vector<std::string> factors;
    int i = 0;
    
    while (i < n) {
        int j = i + 1, k = i;
        
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) {
                k = i;  // Reset reference to start of current Lyndon-like block
            } else {
                k++;    // Continue matching within current base
            }
            j++;
        }
        
        // Extract repeated Lyndon blocks
        while (i <= k) {
            factors.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    
    return factors;
}