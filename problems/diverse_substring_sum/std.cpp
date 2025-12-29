#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    string s;
    cin >> s;
    long long n = s.size();
    long long total = n * (n + 1) / 2;
    long long subtract_sum = 0;
    int max_k = min(20, (int)n);

    for (int k = 1; k <= max_k; k++) {
        long long A = n - k + 1;
        if (k > n) continue;

        vector<uint64_t> masks(n - k + 1);
        uint64_t mask_val = 0;
        for (int j = 0; j < k; j++) {
            mask_val = (mask_val << 1) | (s[j] - '0');
        }
        masks[0] = mask_val;
        uint64_t full_mask = (1ULL << k) - 1;
        for (int i = 1; i < n - k + 1; i++) {
            mask_val = ((mask_val << 1) | (s[i + k - 1] - '0')) & full_mask;
            masks[i] = mask_val;
        }

        int num_masks = 1 << k;
        vector<bool> seen(num_masks, false);
        int l = 0;
        long long f_k = 0;

        for (int r = k - 1; r < n; r++) {
            int current_start = r - k + 1;
            uint64_t current_mask = masks[current_start];
            while (seen[current_mask]) {
                seen[masks[l]] = false;
                l++;
            }
            seen[current_mask] = true;
            f_k += (current_start - l + 1);
        }
        subtract_sum += (A - f_k);
    }

    long long ans = total - subtract_sum;
    cout << ans << '\n';
    return 0;
}