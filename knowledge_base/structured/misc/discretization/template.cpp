#include <bits/stdc++.h>
using namespace std;

// Discretization (Coordinate Compression)
// arr: original array (1-indexed for convenience), n: size
// Returns the discretized array and the mapping from original value to compressed index.
vector<int> discretize(vector<int>& arr) {
    int n = arr.size();
    vector<pair<int, int>> tmp(n); // (value, original index)
    for (int i = 0; i < n; ++i) {
        tmp[i] = {arr[i], i};
    }
    sort(tmp.begin(), tmp.end());
    vector<int> result(n);
    int rank = 0;
    for (int i = 0; i < n; ++i) {
        if (i > 0 && tmp[i].first != tmp[i-1].first) rank++;
        result[tmp[i].second] = rank;
    }
    return result;
}

// Alternative: using unique and lower_bound (common style)
vector<int> discretize_unique(vector<int>& arr) {
    vector<int> sorted = arr;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    vector<int> result(arr.size());
    for (size_t i = 0; i < arr.size(); ++i) {
        result[i] = lower_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin();
    }
    return result;
}

int main() {
    // Example usage
    vector<int> arr = {1000, 30, 30, 500, 1000, 30};
    vector<int> compressed = discretize(arr);
    // compressed: [2, 0, 0, 1, 2, 0]
    return 0;
}