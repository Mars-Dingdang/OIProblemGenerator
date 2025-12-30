#include <iostream>
#include <vector>
using namespace std;

const int N = 100010;
int stk[N], top;
int ls[N], rs[N];
int w[N]; // 权值数组，下标作为k，满足BST

// 构建笛卡尔树，w为权值，n为元素个数
void build_cartesian_tree(int n) {
    top = 0;
    for (int i = 1; i <= n; i++) {
        int k = top;
        while (k > 0 && w[stk[k]] > w[i]) k--;
        if (k) rs[stk[k]] = i;
        if (k < top) ls[i] = stk[k + 1];
        stk[++k] = i;
        top = k;
    }
}