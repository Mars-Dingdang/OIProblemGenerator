// Basic Segment Tree with Lazy Propagation
struct Node {
    long long sum;
    long long lazy;
} tree[4 * MAXN];

void pushup(int p) {
    tree[p].sum = tree[p*2].sum + tree[p*2+1].sum;
}

void pushdown(int p, int l, int r) {
    if (tree[p].lazy) {
        int mid = (l + r) / 2;
        tree[p*2].sum += tree[p].lazy * (mid - l + 1);
        tree[p*2].lazy += tree[p].lazy;
        tree[p*2+1].sum += tree[p].lazy * (r - mid);
        tree[p*2+1].lazy += tree[p].lazy;
        tree[p].lazy = 0;
    }
}

void update(int p, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        tree[p].sum += (long long)v * (r - l + 1);
        tree[p].lazy += v;
        return;
    }
    pushdown(p, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) update(p*2, l, mid, ql, qr, v);
    if (qr > mid) update(p*2+1, mid+1, r, ql, qr, v);
    pushup(p);
}
