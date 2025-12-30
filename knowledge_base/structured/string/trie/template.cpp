struct Trie {
    static const int ALPHABET = 26;
    static const int MAX_NODES = 100000; // adjust as needed
    int trie[MAX_NODES][ALPHABET];
    bool is_end[MAX_NODES];
    int node_count;

    Trie() {
        node_count = 1; // root is node 0
        memset(trie[0], 0, sizeof(trie[0]));
        is_end[0] = false;
    }

    void insert(const string &s) {
        int node = 0;
        for (char ch : s) {
            int idx = ch - 'a';
            if (!trie[node][idx]) {
                memset(trie[node_count], 0, sizeof(trie[node_count]));
                is_end[node_count] = false;
                trie[node][idx] = node_count++;
            }
            node = trie[node][idx];
        }
        is_end[node] = true;
    }

    bool search(const string &s) {
        int node = 0;
        for (char ch : s) {
            int idx = ch - 'a';
            if (!trie[node][idx]) return false;
            node = trie[node][idx];
        }
        return is_end[node];
    }

    bool starts_with(const string &prefix) {
        int node = 0;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!trie[node][idx]) return false;
            node = trie[node][idx];
        }
        return true;
    }
};