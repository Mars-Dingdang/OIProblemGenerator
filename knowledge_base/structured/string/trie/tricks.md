## Key Tricks for Trie

### 1. **01-Trie for XOR Problems**
- Represent numbers as binary strings (LSB to MSB or MSB to LSB depending on problem).
- **Maximum XOR Pair**: For a given number `x`, traverse the trie trying to take the opposite bit at each step to maximize XOR.
- **XOR Range Queries**: Can be combined with prefix XOR arrays.

### 2. **Global Increment (Add-One)**
- For a binary trie, adding 1 to all numbers corresponds to:
  1. Swap left and right children of each node.
  2. Recursively apply to the new left child (which was the original right child).
- This works because binary +1 flips all trailing 1s to 0s and the first 0 to 1.

### 3. **Trie Merging**
- Similar to segment tree merging: recursively merge child nodes.
- Useful for problems requiring union of sets stored in tries (e.g., subtree aggregates).
- Complexity is O(total number of nodes merged).

### 4. **Persistent Trie**
- Maintain multiple versions for temporal queries (e.g., XOR queries on different prefixes).
- Implement by creating new nodes for modified paths, sharing unchanged subtrees.

### 5. **Space Optimization**
- Use `vector<array<int, C>>` or `map<int, int>` for sparse tries.
- For fixed alphabet, array-based implementation is fastest.

### 6. **Multiple End Markers**
- Store additional data at terminal nodes: word frequency, index, or other metadata.

### 7. **Prefix Counting**
- Maintain `cnt[node]` counting how many words pass through this node.
- Enables queries like "how many words have given prefix".

### 8. **Application Patterns**
- **String Set Operations**: Union, intersection via merging.
- **Maximum XOR Subarray**: Combine with prefix XOR and 01-trie.
- **Lexicographic Order**: DFS traversal yields sorted order.
- **Auto-complete**: Traverse from prefix node, collect all words in subtree.

### 9. **Binary Trie for Non-Binary Values**
- Can store integers up to 2^k by using k-bit binary representation.
- Useful for bitwise operations (AND, OR, XOR) on integer sets.

### 10. **Lazy Propagation in 01-Trie**
- For range add operations on binary representations, can use lazy swaps similar to global +1.

### Common Problem Transformations
1. **Tree Path XOR**: `xor(u,v) = xor(root,u) ^ xor(root,v)`.
2. **Subarray XOR**: Convert to prefix XOR then find pairs with target XOR.
3. **Dictionary with Wildcards**: Use multiple tries or traverse all possible wildcard paths.

### Optimization Notes
- For 01-trie with numbers up to 2^31, depth 31-32 is sufficient.
- Memory pool allocation (pre-allocated array) is faster than dynamic allocation.
- Iterative implementation often faster than recursive for insert/search.