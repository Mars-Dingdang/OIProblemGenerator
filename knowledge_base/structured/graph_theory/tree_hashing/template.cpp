#include <iostream>
#include <vector>
#include <random>
#include <set>

using ull = unsigned long long;

const ull mask = std::mt19937_64(time(nullptr))();

ull shift(ull x) {
  x ^= mask;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  x ^= mask;
  return x;
}

constexpr int N = 1e6 + 10;

int n;
ull hash_val[N];
std::vector<int> edge[N];
std::set<ull> trees;

void getHash(int x, int p) {
  hash_val[x] = 1;
  for (int i : edge[x]) {
    if (i == p) continue;
    getHash(i, x);
    hash_val[x] += shift(hash_val[i]);
  }
  trees.insert(hash_val[x]);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  std::cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v;
    std::cin >> u >> v;
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  
  getHash(1, 0);
  std::cout << trees.size() << '\n';
  
  return 0;
}