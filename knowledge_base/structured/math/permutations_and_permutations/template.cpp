#include <vector>
#include <algorithm>
using namespace std;

// 计算逆序数（归并排序版）
long long merge_sort_count(vector<int>& a, int l, int r) {
    if (r - l <= 1) return 0;
    int mid = (l + r) / 2;
    long long res = merge_sort_count(a, l, mid) + merge_sort_count(a, mid, r);
    vector<int> tmp(r - l);
    int i = l, j = mid, k = 0;
    while (i < mid && j < r) {
        if (a[j] < a[i]) {
            tmp[k++] = a[j++];
            res += mid - i;
        } else {
            tmp[k++] = a[i++];
        }
    }
    while (i < mid) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];
    for (i = l, k = 0; i < r; ++i, ++k) a[i] = tmp[k];
    return res;
}

// 计算逆序数（树状数组版，需离散化）
class BIT {
    vector<int> tree;
    int n;
public:
    BIT(int size) : n(size), tree(size + 1, 0) {}
    void add(int idx, int delta) {
        for (; idx <= n; idx += idx & -idx) tree[idx] += delta;
    }
    int sum(int idx) {
        int s = 0;
        for (; idx > 0; idx -= idx & -idx) s += tree[idx];
        return s;
    }
};

long long inversion_count(const vector<int>& arr) {
    vector<int> sorted = arr;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    int m = sorted.size();
    BIT bit(m);
    long long ans = 0;
    for (int i = 0; i < arr.size(); ++i) {
        int id = lower_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin() + 1;
        ans += i - bit.sum(id);
        bit.add(id, 1);
    }
    return ans;
}

// 排列转排名（康托展开）
long long permutation_to_rank(const vector<int>& perm) {
    int n = perm.size();
    BIT bit(n);
    long long fac = 1, rank = 0;
    for (int i = n - 1; i >= 0; --i) {
        rank += bit.sum(perm[i] - 1) * fac;
        bit.add(perm[i], 1);
        fac *= n - i;
    }
    return rank + 1;
}

// 排名转排列（逆康托展开）
vector<int> rank_to_permutation(int n, long long rank) {
    rank--;
    vector<int> lehmer(n);
    for (int i = 1; i <= n; ++i) {
        lehmer[n - i] = rank % i;
        rank /= i;
    }
    BIT bit(n);
    for (int i = 1; i <= n; ++i) bit.add(i, 1);
    vector<int> perm(n);
    for (int i = 0; i < n; ++i) {
        int l = 1, r = n;
        while (l < r) {
            int mid = (l + r) / 2;
            if (bit.sum(mid) >= lehmer[i] + 1) r = mid;
            else l = mid + 1;
        }
        perm[i] = l;
        bit.add(l, -1);
    }
    return perm;
}