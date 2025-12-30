#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Example: Minimum cost to make sequence non-decreasing (BalticOI 2004 Sequence)
long long slope_trick_sequence(const vector<int>& a) {
    int n = a.size();
    vector<int> b(n);
    long long res = 0;
    priority_queue<int> max_heap; // stores breakpoints (negative slope side)
    for (int i = 0; i < n; ++i) {
        int val = a[i] - i; // adjust for strict increasing
        max_heap.push(val);
        max_heap.push(val);
        res += max_heap.top() - val;
        max_heap.pop();
        b[i] = max_heap.top();
    }
    // Reconstruct optimal sequence (optional)
    for (int i = n - 2; i >= 0; --i) b[i] = min(b[i], b[i + 1]);
    for (int i = 0; i < n; ++i) b[i] += i; // revert adjustment
    return res;
}

// Example: Stock trading (CF 865D Buy Low Sell High)
long long slope_trick_stock(const vector<int>& prices) {
    long long profit = 0;
    priority_queue<int> max_heap; // stores negative slopes
    for (int p : prices) {
        max_heap.push(-p);
        max_heap.push(-p);
        profit += p + max_heap.top();
        max_heap.pop();
    }
    return profit;
}

int main() {
    // Example usage
    vector<int> seq = {2, 5, 3, 1, 4};
    cout << slope_trick_sequence(seq) << endl;
    vector<int> prices = {1, 2, 3, 4, 5};
    cout << slope_trick_stock(prices) << endl;
    return 0;
}