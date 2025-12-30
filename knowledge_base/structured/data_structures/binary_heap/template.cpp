#include <vector>
#include <algorithm>

const int MAXN = 100010;
int h[MAXN], n = 0; // h: heap array, n: current size

void up(int x) {
  while (x > 1 && h[x] > h[x / 2]) {
    std::swap(h[x], h[x / 2]);
    x /= 2;
  }
}

void down(int x) {
  int t;
  while (x * 2 <= n) {
    t = x * 2;
    if (t + 1 <= n && h[t + 1] > h[t]) t++;
    if (h[t] <= h[x]) break;
    std::swap(h[x], h[t]);
    x = t;
  }
}

void insert(int val) {
  h[++n] = val;
  up(n);
}

int get_max() {
  return h[1];
}

void delete_max() {
  std::swap(h[1], h[n]);
  n--;
  down(1);
}

void build_heap() {
  for (int i = n / 2; i >= 1; i--) {
    down(i);
  }
}