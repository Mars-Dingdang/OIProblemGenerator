int anc[N];
vector<int> topo;

void find_descendants(vector<int>& S, int u, vector<int>& result) {
    if (S.empty()) return;
    vector<int> temp = S;
    while (!temp.empty()) {
        clear();
        for (int x : temp) add(x);
        add(1);
        if (!query(u)) break; // no descendant of u in temp
        
        if (temp.size() == 1) {
            result.push_back(temp[0]);
            // remove from S
            S.erase(remove(S.begin(), S.end(), temp[0]), S.end());
            temp.clear();
        } else {
            int mid = temp.size() / 2;
            vector<int> L(temp.begin(), temp.begin() + mid);
            vector<int> R(temp.begin() + mid, temp.end());
            
            clear();
            for (int x : L) add(x);
            add(1);
            if (query(u)) {
                temp = L;
            } else {
                temp = R;
            }
        }
    }
}

void solve(int x, vector<int>& S) {
    if (S.size() <= 1) return;
    
    // Find one descendant y of x in S\{x}
    vector<int> candidates = S;
    candidates.erase(remove(candidates.begin(), candidates.end(), x), candidates.end());
    if (candidates.empty()) return;
    
    clear();
    for (int z : candidates) add(z);
    add(1);
    if (!query(x)) return; // no descendant
    
    // Binary search to find one descendant
    vector<int> T = candidates;
    while (T.size() > 1) {
        int mid = T.size() / 2;
        vector<int> L(T.begin(), T.begin() + mid);
        vector<int> R(T.begin() + mid, T.end());
        
        clear();
        for (int z : L) add(z);
        add(1);
        if (query(x)) {
            T = L;
        } else {
            T = R;
        }
    }
    int y = T[0];
    
    // Recurse on y's subtree
    vector<int> Sy;
    for (int z : S) {
        clear(); add(y); add(1);
        if (query(z)) { // z is in y's subtree?
            Sy.push_back(z);
        }
    }
    solve(y, Sy);
    
    // Append Sy (excluding y?) to topo? Actually, solved inside
    // Remove Sy from S
    for (int z : Sy) {
        S.erase(remove(S.begin(), S.end(), z), S.end());
    }
    
    // Continue with remaining part of S
    solve(x, S); // tail recursion
}

void work(int n) {
    vector<int> all;
    for (int i = 1; i <= n; i++) all.push_back(i);
    
    solve(1, all);
    
    // Now topo has nodes in reverse topological order?
    // Reconstruct parent-child relationships
    vector<set<int>> ancestor(n+1);
    for (int i = 1; i <= n; i++) {
        clear(); add(1); add(i);
        for (int j = 1; j <= n; j++) {
            if (query(j)) {
                ancestor[i].insert(j);
            }
        }
    }
    
    // For each node i, find parent
    for (int i = 2; i <= n; i++) {
        int parent = -1;
        int max_anc_size = -1;
        for (int a : ancestor[i]) {
            if (a == i) continue;
            if (ancestor[a].size() > max_anc_size && ancestor[a] != ancestor[i]) {
                // Check subset: actually should be strict subset
                bool subset = true;
                for (int x : ancestor[a]) {
                    if (ancestor[i].find(x) == ancestor[i].end()) {
                        subset = false; break;
                    }
                }
                if (subset && ancestor[a].size() > max_anc_size) {
                    max_anc_size = ancestor[a].size();
                    parent = a;
                }
            }
        }
        if (parent != -1) {
            report(parent, i);
        }
    }
}