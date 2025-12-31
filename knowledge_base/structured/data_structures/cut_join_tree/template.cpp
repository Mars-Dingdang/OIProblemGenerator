struct Node {
    char type; // 'L' (leaf), 'J' (join), 'C' (cut)
    int l, r;
    std::vector<Node*> children;
    Node(char t, int left, int right) : type(t), l(left), r(right) {}
};

// Linear-time Cut-Join Tree Construction from Pseudo-Minimal Interval Sequence
// Input: l[i], r[i] for i in [0, n-2] representing [l_i, r_i] for each [i+1, i+2]
std::stack<Node*> constructCutJoinTree(const std::vector<int>& l, const std::vector<int>& r, int n) {
    std::stack<Node*> s; // Stack of nodes
    std::stack<int> t;  // Stack of left endpoints

    // Extend l and r arrays to size n (r[n-1] unused)
    std::vector<int> L = l, R = r;
    L.push_back(1); // dummy

    for (int i = 1; i <= n; ++i) {
        Node* u = new Node('L', i, i);

        while (!t.empty() && R[t.top()-1] <= i) { // R is 0-indexed
            int j = s.size();
            std::vector<Node*> temp;
            while (j >= 1 && s.top()->l > t.top()) {
                temp.push_back(s.top()); s.pop(); --j;
            }
            std::reverse(temp.begin(), temp.end());
            temp.push_back(u);

            Node* last = s.top();
            if (j == (int)s.size() && last->type == 'J' && 
                L[last->r-1] >= last->children.back()->l) {
                // Merge into existing join node
                for (auto child : temp) last->children.push_back(child);
                last->r = i;
                u = last;
            } else {
                Node* v;
                if (j == (int)s.size()) {
                    v = new Node('J', last->l, i);
                    v->children = {last, u};
                } else {
                    v = new Node('C', s.top()->l, i);
                    std::vector<Node*> all;
                    while ((int)s.size() >= j) {
                        all.push_back(s.top()); s.pop();
                    }
                    std::reverse(all.begin(), all.end());
                    all.push_back(u);
                    v->children = all;
                }
                u = v;
            }
            t.pop();
        }

        s.push(u);
        t.push(u->l);
        while (!t.empty() && t.top() > L[i-1]) t.pop(); // L[i-1] for position i
        if (!t.empty()) {
            // Update R value for top of t stack (if needed)
            // In practice, R should be maintained separately
        }
    }

    return s; // contains root
}

// Note: This is a conceptual translation of Algorithm 2.
// Full implementation requires careful indexing and maintenance of R values in stack t.
// For production use, refer to known efficient implementations of cut-join trees.