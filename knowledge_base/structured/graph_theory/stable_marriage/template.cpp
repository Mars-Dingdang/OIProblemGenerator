#include <iostream>
#include <queue>
#include <vector>

struct StableMatching {
  int nx, ny;
  std::vector<std::vector<int>> pref_x, pref_y;
  std::vector<int> match_x, match_y;

  StableMatching(int nx, int ny)
      : nx(nx),
        ny(ny),
        pref_x(nx),
        pref_y(ny),
        match_x(nx, -1),
        match_y(ny, -1) {}

  void solve() {
    std::vector<std::vector<int>> ranks(ny, std::vector<int>(nx));
    for (int j = 0; j != ny; ++j) {
      for (int i = 0; i != pref_y[j].size(); ++i) {
        ranks[j][pref_y[j][i]] = nx - i;
      }
    }

    std::vector<int> waitlist(ny);
    std::vector<int> ids(nx);
    std::queue<int> q;
    for (int i = 0; i != nx; ++i) q.push(i);

    while (!q.empty()) {
      auto i = q.front();
      q.pop();
      if (ids[i] >= pref_x[i].size()) continue;
      auto j = pref_x[i][ids[i]++];
      if (ranks[j][i] > waitlist[j]) {
        if (waitlist[j]) {
          int prev_i = pref_y[j][nx - waitlist[j]];
          match_x[prev_i] = -1;
          q.push(prev_i);
        }
        waitlist[j] = ranks[j][i];
        match_x[i] = j;
      } else {
        q.push(i);
      }
    }

    for (int j = 0; j != ny; ++j) {
      if (waitlist[j]) {
        int i = pref_y[j][nx - waitlist[j]];
        match_y[j] = i;
      }
    }
  }
};