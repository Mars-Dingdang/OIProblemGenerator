#include <iostream>
#include <vector>
using namespace std;

// Example: O(n^2) algorithm
void example_quadratic(int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Some constant-time operation
            cout << i << ", " << j << endl;
        }
    }
}

// Example: O(n log n) algorithm (merge sort style)
void example_nlogn(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    example_nlogn(arr, l, mid);
    example_nlogn(arr, mid + 1, r);
    // Merge step O(n)
    vector<int> temp;
    int i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= r) temp.push_back(arr[j++]);
    for (int k = 0; k < temp.size(); ++k) arr[l + k] = temp[k];
}

int main() {
    int n = 10;
    example_quadratic(n);
    vector<int> arr = {5, 2, 9, 1, 5, 6};
    example_nlogn(arr, 0, arr.size() - 1);
    return 0;
}