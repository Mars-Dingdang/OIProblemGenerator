/*
This is a conceptual C++ template based on the algorithm described.
Full implementation would require careful indexing and memory management.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;
const int MAXN = 200010; // Adjust based on constraints

// State vector types
typedef array<ll, 2> NodeState;        // [black_val, white_val]
typedef array<ll, 4> EdgeWeight;       // [w00, w01, w10, w11]
typedef array<ll, 4> Point4;           // Generic 4-element array for matrices

typedef array<array<ll, 4>, 4> Mat4x4;  // 4x4 matrix for transformations

typedef array<array<ll, 2>, 2> Mat2x2;  // 2x2 matrix for node ops

struct ExprNode {
    int op; // 0: leaf, 1:+, 2:*, 3:⊕, 4:R
    int ch[3], deg; // children
    EdgeWeight ew;  // for edge
    NodeState ns;   // for node
    int rev;        // reversed flag
    int heavy;      // heavy child index
    Mat4x4 mat;     // transformation matrix
};

vector<ExprNode> expr;
vector<int> G[MAXN]; // original graph

// Build expression tree using reduction rules
void build_expression_tree() {
    // Step 1: initialize leaves for edges and nodes
    // Step 2: simulate reduction: while |V| > 1
    //   - pick degree-1 node -> apply ⊕
    //   - else pick degree-2 node -> apply *
    //   - else merge multi-edge -> apply +
    // Record operations in expr tree
}

// Compute transformation matrix based on operation and heavy child
Mat4x4 compute_matrix(int u) {
    auto &e = expr[u];
    if (e.op == 1) { // + : merge edges
        Mat4x4 res = {{{-INF}}};
        auto sib = expr[e.ch[e.heavy ^ 1]].ew;
        res[0][0] = sib[0]; res[1][1] = sib[1];
        res[2][2] = sib[2]; res[3][3] = sib[3];
        return res;
    } else if (e.op == 4) { // R : reverse
        Mat4x4 res = {{{-INF}}};
        res[0][0] = 0; res[1][2] = 0;
        res[2][1] = 0; res[3][3] = 0;
        return res;
    } else if (e.op == 2) { // * : contract degree-2
        auto e1 = expr[e.ch[0]].ew, e2 = expr[e.ch[2]].ew;
        auto mid = expr[e.ch[1]].ns;
        Mat4x4 res;
        if (e.heavy == 0) {
            // left edge is heavy
            res[0][0] = mid[0] + e2[0]; res[0][1] = mid[1] + e2[2];
            res[1][0] = mid[0] + e2[1]; res[1][1] = mid[1] + e2[3];
            res[2][0] = mid[0] + e2[0]; res[2][1] = mid[1] + e2[2];
            res[3][0] = mid[0] + e2[1]; res[3][1] = mid[1] + e2[3];
        } else if (e.heavy == 2) {
            // right edge is heavy
            res[0][0] = e1[0] + mid[0]; res[0][2] = e1[1] + mid[1];
            res[1][0] = e1[0] + mid[0]; res[1][2] = e1[1] + mid[1];
            res[2][0] = e1[2] + mid[0]; res[2][2] = e1[3] + mid[1];
            res[3][0] = e1[2] + mid[0]; res[3][2] = e1[3] + mid[1];
        } else { // middle node is heavy — rare case
            // Requires full computation
        }
        return res;
    } else if (e.op == 3) { // ⊕ : remove degree-1
        auto u = expr[e.ch[0]].ns, e0 = expr[e.ch[1]].ew, v = expr[e.ch[2]].ns;
        Mat2x2 res;
        if (e.heavy == 0) {
            res[0][0] = max(e0[0] + v[0], e0[1] + v[1]);
            res[1][1] = max(e0[2] + v[0], e0[3] + v[1]);
        } else if (e.heavy == 2) {
            res[0][0] = u[0] + e0[0]; res[0][1] = u[0] + e0[1];
            res[1][0] = u[1] + e0[2]; res[1][1] = u[1] + e0[3];
        } else {
            // heavy is edge
            res[0][0] = u[0] + v[0]; res[0][1] = u[0] + v[1];
            res[1][0] = u[1] + v[0]; res[1][1] = u[1] + v[1];
        }
        // Convert to 4x4? Or use separate logic
    }
    return Mat4x4{{{}}};
}

// Segment tree for heavy paths
class SegTree {
public:
    virtual void update(int i) = 0;
    virtual Mat4x4 query(int l, int r) = 0;
};

// Heavy-Light Decomposition on expression tree
class HLD {
public:
    void init() {}
    void modify(int u) {
        // Traverse path to root, update segtrees
    }
    NodeState get_answer() {
        // Return root state
        return NodeState{};
    }
};

// Main solver
class ParkSolver {
    HLD hld;
public:
    void preprocess() {
        build_expression_tree();
        hld.init();
    }

    ll solve() {
        auto ans = hld.get_answer();
        return max(ans[0], ans[1]);
    }

    void update_node(int id, ll b, ll w) {
        // Update leaf, propagate
    }

    void update_edge(int id, ll s, ll d) {
        // Update edge weight (s=same, d=different)
        // Map to w00=s, w01=d, w10=d, w11=s
    }
};
