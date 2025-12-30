#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct SequenceAutomaton {
    vector<vector<int>> next;
    int n;
    const string &s;
    
    SequenceAutomaton(const string &str) : s(str), n(str.size()) {
        next.assign(n + 1, vector<int>(26, n + 1));
        vector<int> last(26, n + 1);
        
        for (int i = n; i >= 0; --i) {
            if (i > 0) {
                int c = s[i - 1] - 'a';
                last[c] = i;
            }
            for (int j = 0; j < 26; ++j) {
                next[i][j] = last[j];
            }
        }
    }
    
    // Check if t is a subsequence of s
    bool isSubsequence(const string &t) {
        int state = 0;
        for (char ch : t) {
            int c = ch - 'a';
            state = next[state][c];
            if (state > n) return false;
        }
        return true;
    }
    
    // Get next state after reading character c from current state
    int transition(int state, char ch) {
        int c = ch - 'a';
        return next[state][c];
    }
};