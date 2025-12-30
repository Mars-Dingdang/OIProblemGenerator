#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

class BoyerMoore {
private:
    string pattern;
    vector<int> bad_char_shift;
    vector<int> good_suffix_shift;
    vector<int> suffixes;
    
    void preprocess_bad_char() {
        int m = pattern.size();
        bad_char_shift.assign(256, m);  // ASCII assumption
        for (int i = 0; i < m - 1; ++i) {
            bad_char_shift[(unsigned char)pattern[i]] = m - 1 - i;
        }
    }
    
    void compute_suffixes() {
        int m = pattern.size();
        suffixes.resize(m);
        suffixes[m - 1] = m;
        int g = m - 1, f = 0;
        for (int i = m - 2; i >= 0; --i) {
            if (i > g && suffixes[i + m - 1 - f] < i - g) {
                suffixes[i] = suffixes[i + m - 1 - f];
            } else {
                g = min(g, i);
                f = i;
                while (g >= 0 && pattern[g] == pattern[g + m - 1 - f]) {
                    --g;
                }
                suffixes[i] = f - g;
            }
        }
    }
    
    void preprocess_good_suffix() {
        int m = pattern.size();
        compute_suffixes();
        good_suffix_shift.assign(m, m);
        
        // Case 2
        for (int i = 0, j = 0; i < m; ++i) {
            if (suffixes[i] == i + 1) {
                for (; j < m - 1 - i; ++j) {
                    if (good_suffix_shift[j] == m) {
                        good_suffix_shift[j] = m - 1 - i;
                    }
                }
            }
        }
        
        // Case 1
        for (int i = 0; i < m - 1; ++i) {
            good_suffix_shift[m - 1 - suffixes[i]] = m - 1 - i;
        }
    }
    
public:
    BoyerMoore(const string& pat) : pattern(pat) {
        preprocess_bad_char();
        preprocess_good_suffix();
    }
    
    vector<int> search(const string& text) {
        vector<int> matches;
        int n = text.size();
        int m = pattern.size();
        
        int i = 0;
        while (i <= n - m) {
            int j = m - 1;
            while (j >= 0 && pattern[j] == text[i + j]) {
                --j;
            }
            if (j < 0) {
                matches.push_back(i);
                i += good_suffix_shift[0];
            } else {
                int bc_shift = bad_char_shift[(unsigned char)text[i + j]] - (m - 1 - j);
                int gs_shift = good_suffix_shift[j];
                i += max(bc_shift, gs_shift);
            }
        }
        return matches;
    }
};

// Usage example:
// BoyerMoore bm("EXAMPLE");
// vector<int> positions = bm.search("HERE IS A SIMPLE EXAMPLE...");