struct DFA {
  int m;                                // Alphabet size.
  int n;                                // Number of states.
  int q0;                               // Initial state.
  std::vector<std::vector<int>> trans;  // Transitions: trans[c][q].
  std::vector<int> acc;                 // Acceptance labels per state.

  DFA(int m, int n = 0, int q0 = 0)
      : m(m), n(n), q0(q0), trans(m, std::vector<int>(n)), acc(n) {}

  // Simulate the DFA on string w
  bool accepts(const std::string& w) const {
    int state = q0;
    for (char c : w) {
      int idx = c - '0'; // assuming binary alphabet
      if (state >= trans[idx].size()) return false;
      state = trans[idx][state];
    }
    return acc[state];
  }
};