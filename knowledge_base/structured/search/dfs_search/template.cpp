#include <iostream>
#include <vector>
using namespace std;

// Example: Generating all permutations of size n
vector<int> current;
vector<bool> used;
int n;

void dfs(int depth) {
    if (depth == n) {
        // Process a complete permutation
        for (int x : current) cout << x << ' ';
        cout << '\n';
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            used[i] = true;
            current.push_back(i);
            dfs(depth + 1);
            current.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    cin >> n;
    used.resize(n + 1, false);
    dfs(0);
    return 0;
}