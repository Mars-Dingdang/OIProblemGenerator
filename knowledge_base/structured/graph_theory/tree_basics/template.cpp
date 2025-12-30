#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> adj[N]; // adjacency list for undirected tree
int parent[N];
int depth[N];

// DFS to compute parent and depth (assuming root = 1)
void dfs(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
}

// BFS / Level Order Traversal
vector<vector<int>> levelOrder(int root, int n) {
    vector<vector<int>> levels;
    queue<int> q;
    vector<bool> vis(n+1, false);
    q.push(root);
    vis[root] = true;
    while (!q.empty()) {
        int sz = q.size();
        vector<int> cur;
        for (int i = 0; i < sz; ++i) {
            int u = q.front(); q.pop();
            cur.push_back(u);
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        levels.push_back(cur);
    }
    return levels;
}

// Binary Tree Node Structure
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Preorder Traversal (Recursive)
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

// Morris Inorder Traversal (O(1) space)
void morrisInorder(TreeNode* root) {
    TreeNode* cur = root;
    while (cur) {
        if (!cur->left) {
            cout << cur->val << " ";
            cur = cur->right;
        } else {
            TreeNode* mostRight = cur->left;
            while (mostRight->right && mostRight->right != cur) {
                mostRight = mostRight->right;
            }
            if (!mostRight->right) {
                mostRight->right = cur;
                cur = cur->left;
            } else {
                mostRight->right = nullptr;
                cout << cur->val << " ";
                cur = cur->right;
            }
        }
    }
}

int main() {
    // Example usage
    int n; // number of nodes
    cin >> n;
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0); // root = 1
    return 0;
}