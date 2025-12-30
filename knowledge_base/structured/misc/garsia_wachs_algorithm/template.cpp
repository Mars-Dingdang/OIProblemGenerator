#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class GarsiaWachs {
public:
    static long long solve(vector<long long>& a) {
        int n = a.size();
        if (n == 0) return 0;
        
        vector<long long> num;
        num.push_back(LLONG_MAX); // sentinel
        for (int i = 0; i < n; ++i) {
            num.push_back(a[i]);
        }
        num.push_back(LLONG_MAX); // sentinel
        
        long long ans = 0;
        
        while (num.size() > 3) {
            int k = -1;
            // Find smallest i such that num[i-1] <= num[i+1]
            for (int i = 1; i < num.size() - 1; ++i) {
                if (num[i-1] <= num[i+1]) {
                    k = i;
                    break;
                }
            }
            if (k == -1) break;
            
            long long temp = num[k-1] + num[k];
            ans += temp;
            
            // Remove num[k-1] and num[k]
            num.erase(num.begin() + k - 1, num.begin() + k + 1);
            
            // Find largest j such that num[j] > temp
            int j = -1;
            for (int i = k - 2; i >= 0; --i) {
                if (num[i] > temp) {
                    j = i;
                    break;
                }
            }
            
            // Insert temp after position j
            num.insert(num.begin() + j + 1, temp);
        }
        
        return ans;
    }
};