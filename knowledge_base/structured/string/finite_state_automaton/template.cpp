struct NFA {
    int n; // number of states
    vector<unordered_set<int>> eps; // epsilon transitions
    vector<vector<unordered_set<int>>> trans; // trans[state][c] = set of next states
    vector<bool> accept;

    NFA(int states) : n(states), eps(states), trans(states, vector<unordered_set<int>>(10)), accept(states, false) {}

    void add_epsilon(int u, int v) {
        eps[u].insert(v);
    }

    void add_trans(int u, char c, int v) {
        trans[u][c - '0'].insert(v);
    }

    // Simulate NFA on string s using bitset optimization
    bool matches(const string& s) {
        vector<bool> curr(n, false);
        queue<int> q;

        // Compute epsilon closure of start state (0)
        vector<bool> visited(n, false);
        q.push(0);
        visited[0] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            curr[u] = true;
            for (int v : eps[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        for (char c : s) {
            vector<bool> next_state(n, false);
            // Process character transition
            for (int u = 0; u < n; u++) {
                if (curr[u]) {
                    for (int v : trans[u][c - '0']) {
                        next_state[v] = true;
                    }
                }
            }
            // Reset visited for epsilon BFS
            fill(visited.begin(), visited.end(), false);
            queue<int> qq;
            for (int u = 0; u < n; u++) {
                if (next_state[u]) {
                    if (!visited[u]) {
                        visited[u] = true;
                        qq.push(u);
                    }
                }
            }
            // Epsilon closure
            while (!qq.empty()) {
                int u = qq.front(); qq.pop();
                for (int v : eps[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        qq.push(v);
                        next_state[v] = true;
                    }
                }
            }
            curr = move(next_state);
        }

        for (int u = 0; u < n; u++) {
            if (curr[u] && accept[u]) return true;
        }
        return false;
    }
};