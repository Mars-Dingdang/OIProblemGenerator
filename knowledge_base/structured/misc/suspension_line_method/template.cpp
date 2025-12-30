#include <algorithm>
#include <iostream>
constexpr int N = 100010;
int n, a[N];
int l[N], r[N];
long long ans;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  while (std::cin >> n, n) {
    ans = 0;
    for (int i = 1; i <= n; i++) {
      std::cin >> a[i];
      l[i] = r[i] = i;
    }
    for (int i = 1; i <= n; i++)
      while (l[i] > 1 && a[i] <= a[l[i] - 1]) l[i] = l[l[i] - 1];
    for (int i = n; i >= 1; i--)
      while (r[i] < n && a[i] <= a[r[i] + 1]) r[i] = r[r[i] + 1];
    for (int i = 1; i <= n; i++)
      ans = std::max(ans, (long long)(r[i] - l[i] + 1) * a[i]);
    std::cout << ans << '\n';
  }
  return 0;
}