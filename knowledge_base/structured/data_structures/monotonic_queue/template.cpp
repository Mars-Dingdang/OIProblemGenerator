#include <iostream>
#include <deque>
#include <vector>
using namespace std;

void sliding_window_min_max(vector<int>& a, int k) {
    deque<int> dq_min, dq_max;
    int n = a.size();

    for (int i = 0; i < n; ++i) {
        while (!dq_min.empty() && dq_min.front() <= i - k) dq_min.pop_front();
        while (!dq_min.empty() && a[dq_min.back()] >= a[i]) dq_min.pop_back();
        dq_min.push_back(i);

        while (!dq_max.empty() && dq_max.front() <= i - k) dq_max.pop_front();
        while (!dq_max.empty() && a[dq_max.back()] <= a[i]) dq_max.pop_back();
        dq_max.push_back(i);

        if (i >= k - 1) {
            cout << a[dq_min.front()] << ' ';
        }
    }
    cout << '\n';

    for (int i = 0; i < n; ++i) {
        if (i >= k - 1) {
            cout << a[dq_max.front()] << ' ';
        }
    }
    cout << '\n';
}