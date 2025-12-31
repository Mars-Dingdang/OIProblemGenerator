/*
 * Simplified implementation of Bit-Compressed Trie and vEB Tree
 * Based on the paper by Qian Yi
 */

#include <bits/stdc++.h>
using namespace std;

// —————————————— Bit-Compressed Trie (w = 64) ——————————————
const int W = 64;
typedef long long ll;

struct BitTrie {
    int k; // current level: represents [0, 2^k)
    ll mask; // tracks non-empty children
    vector<BitTrie*> children;

    BitTrie(int _k) : k(_k), mask(0) {
        if (k <= 6) return; // leaf: use mask only
        int c = 6; // log2(W)
        int nk = k - c;
        children.resize(1 << c, nullptr);
    }

    ~BitTrie() {
        for (auto* ch : children) delete ch;
    }

    void insert(int x) {
        if (k <= 6) {
            mask |= (1LL << x);
            return;
        }
        int c = 6;
        int high = x >> (k - c);
        int low = x & ((1 << (k - c)) - 1);

        if (!children[high]) {
            children[high] = new BitTrie(k - c);
            mask |= (1LL << high); // mark non-empty
        }
        children[high]->insert(low);
    }

    void erase(int x) {
        if (k <= 6) {
            mask &= ~(1LL << x);
            return;
        }
        int c = 6;
        int high = x >> (k - c);
        int low = x & ((1 << (k - c)) - 1);

        auto* ch = children[high];
        if (!ch) return;
        ch->erase(low);

        // if child becomes empty
        if (ch->mask == 0) {
            delete ch;
            children[high] = nullptr;
            mask &= ~(1LL << high);
        }
    }

    int pred(int x) {
        if (k <= 6) {
            ll bits = mask & ((1LL << x) - 1);
            if (!bits) return -1;
            return 63 - __builtin_clzll(bits);
        }
        int c = 6;
        int high = x >> (k - c);
        int low = x & ((1 << (k - c)) - 1);

        // try same high part
        if (children[high]) {
            int p = children[high]->pred(low);
            if (p != -1) return (high << (k - c)) + p;
        }

        // find previous non-empty high
        ll prev_highs = mask & ((1LL << high) - 1);
        if (!prev_highs) return -1;
        int h = 63 - __builtin_clzll(prev_highs);
        return (h << (k - c)) + children[h]->max_in_subtree();
    }

    int succ(int x) {
        if (k <= 6) {
            ll bits = mask & (~((1LL << (x+1)) - 1));
            if (!bits) return -1;
            return __builtin_ctzll(bits);
        }
        int c = 6;
        int high = x >> (k - c);
        int low = x & ((1 << (k - c)) - 1);

        // try same high part
        if (children[high]) {
            int s = children[high]->succ(low);
            if (s != -1) return (high << (k - c)) + s;
        }

        // find next non-empty high
        ll next_highs = mask & ~((1LL << (high + 1)) - 1);
        if (!next_highs) return -1;
        int h = __builtin_ctzll(next_highs);
        return (h << (k - c)) + children[h]->min_in_subtree();
    }

    int max_in_subtree() {
        if (k <= 6) return mask ? (63 - __builtin_clzll(mask)) : -1;
        int h = 63 - __builtin_clzll(mask);
        return (h << (k - 6)) + children[h]->max_in_subtree();
    }

    int min_in_subtree() {
        if (k <= 6) return mask ? __builtin_ctzll(mask) : -1;
        int h = __builtin_ctzll(mask);
        return (h << (k - 6)) + children[h]->min_in_subtree();
    }
};


// —————————————— vEB Tree (Simplified) ——————————————
struct VEB {
    int u; // universe size: [0, u)
    int min = -1, max = -1;
    VEB *summary = nullptr;
    vector<VEB*> clusters;

    VEB(int _u) : u(_u) {
        if (u <= 2) return;
        int sqrt_u = 1 << (int)((__builtin_clz(1) - __builtin_clz(u - 1) + 1) / 2);
        int num_clusters = (u + sqrt_u - 1) / sqrt_u;
        clusters.resize(num_clusters, nullptr);
        summary = new VEB(num_clusters);
    }

    int high(int x, int sqrt_u) { return x / sqrt_u; }
    int low(int x, int sqrt_u) { return x % sqrt_u; }
    int index(int hi, int lo, int sqrt_u) { return hi * sqrt_u + lo; }

    bool contains(int x) {
        if (min == x || max == x) return true;
        if (u <= 2) return false;
        int sqrt_u = 1 << (int)((__builtin_clz(1) - __builtin_clz(u - 1) + 1) / 2);
        int h = high(x, sqrt_u), l = low(x, sqrt_u);
        if (!clusters[h]) return false;
        return clusters[h]->contains(l);
    }

    void insert(int x) {
        if (min == -1) {
            min = max = x;
            return;
        }
        if (x < min) swap(x, min);
        if (x == min) return;
        if (x > max) max = x;

        if (u <= 2) return;

        int sqrt_u = 1 << (int)((__builtin_clz(1) - __builtin_clz(u - 1) + 1) / 2);
        int h = high(x, sqrt_u), l = low(x, sqrt_u);

        if (!clusters[h]) {
            clusters[h] = new VEB(sqrt_u);
            summary->insert(h);
        }
        clusters[h]->insert(l);
    }

    void remove(int x) {
        if (min == max) {
            if (min == x) min = max = -1;
            return;
        }
        if (x == min) {
            int h = summary->min;
            int l = clusters[h]->min;
            min = index(h, l, 1 << (int)((__builtin_clz(1) - __builtin_clz(u - 1) + 1) / 2));
            x = min;
        }
        if (u <= 2) {
            if (x == max) max = min;
            return;
        }
        int sqrt_u = 1 << (int)((__builtin_clz(1) - __builtin_clz(u - 1) + 1) / 2);
        int h = high(x, sqrt_u), l = low(x, sqrt_u);
        if (!clusters[h]) return;
        clusters[h]->remove(l);
        if (clusters[h]->min == -1) {
            delete clusters[h];
            clusters[h] = nullptr;
            summary->remove(h);
        }
        if (x == max) {
            if (summary->max == -1) max = min;
            else {
                int h = summary->max;
                max = index(h, clusters[h]->max, sqrt_u);
            }
        }
    }

    int pred(int x) {
        if (min == -1 || x <= min) return -1;
        if (x > max) return max;

        if (u <= 2) return min;

        int sqrt_u = 1 << (int)((__builtin_clz(1) - __builtin_clz(u - 1) + 1) / 2);
        int h = high(x, sqrt_u), l = low(x, sqrt_u);

        int res = -1;
        if (clusters[h] && clusters[h]->max >= 0 && clusters[h]->min < l) {
            int p = clusters[h]->pred(l);
            if (p != -1) res = index(h, p, sqrt_u);
        }
        if (res != -1) return res;

        int h_pred = summary->pred(h);
        if (h_pred == -1) return min; // global min

        int max_in_prev = clusters[h_pred]->max;
        return index(h_pred, max_in_prev, sqrt_u);
    }

    int succ(int x) {
        if (min == -1 || x >= max) return -1;
        if (x < min) return min;

        if (u <= 2) return max;

        int sqrt_u = 1 << (int)((__builtin_clz(1) - __builtin_clz(u - 1) + 1) / 2);
        int h = high(x, sqrt_u), l = low(x, sqrt_u);

        if (clusters[h] && clusters[h]->min < clusters[h]->u && clusters[h]->max > l) {
            int s = clusters[h]->succ(l);
            if (s != -1) return index(h, s, sqrt_u);
        }

        int h_succ = summary->succ(h);
        if (h_succ == -1) return -1;

        int min_in_next = clusters[h_succ]->min;
        return index(h_succ, min_in_next, sqrt_u);
    }
};