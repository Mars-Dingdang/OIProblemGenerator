#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1e4 + 5;
const int MAXQ = 1e7 + 7;

int n, m;
vector<pair<int, int>> g[MAXN];
bool vis[MAXN], ans[105];
int query[105];
bool bucket[MAXQ];

int getSize(int u, int parent) {
    int size = 1;
    for (auto &e : g[u]) {
        int v = e.first;
        if (v != parent && !vis[v]) {
            size += getSize(v, u);
        }
    }
    return size;
}

int getCentroid(int u, int parent, int totalSize) {
    for (auto &e : g[u]) {
        int v = e.first;
        if (v != parent && !vis[v] && getSize(v, u) > totalSize / 2) {
            return getCentroid(v, u, totalSize);
        }
    }
    return u;
}

void getDistances(int u, int parent, int dist, vector<int> &distances) {
    distances.push_back(dist);
    for (auto &e : g[u]) {
        int v = e.first, w = e.second;
        if (v != parent && !vis[v]) {
            getDistances(v, u, dist + w, distances);
        }
    }
}

void solve(int u) {
    int totalSize = getSize(u, -1);
    int centroid = getCentroid(u, -1, totalSize);
    
    vis[centroid] = true;
    
    // Process paths passing through centroid
    bucket[0] = true;  // distance 0 always exists
    vector<int> seenDists;
    
    for (auto &e : g[centroid]) {
        int v = e.first, w = e.second;
        if (!vis[v]) {
            vector<int> distances;
            getDistances(v, centroid, w, distances);
            
            // Check queries
            for (int q = 0; q < m; q++) {
                if (ans[q]) continue;
                for (int d : distances) {
                    if (query[q] >= d && bucket[query[q] - d]) {
                        ans[q] = true;
                        break;
                    }
                }
            }
            
            // Add these distances to global bucket
            for (int d : distances) {
                if (d < MAXQ) {
                    bucket[d] = true;
                    seenDists.push_back(d);
                }
            }
        }
    }
    
    // Clean up bucket
    bucket[0] = false;
    for (int d : seenDists) {
        if (d < MAXQ) bucket[d] = false;
    }
    
    // Recursively solve subtrees
    for (auto &e : g[centroid]) {
        int v = e.first;
        if (!vis[v]) {
            solve(v);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    
    for (int i = 0; i < m; i++) {
        cin >> query[i];
    }
    
    solve(1);
    
    for (int i = 0; i < m; i++) {
        cout << (ans[i] ? "AYE" : "NAY") << '\n';
    }
    
    return 0;
}