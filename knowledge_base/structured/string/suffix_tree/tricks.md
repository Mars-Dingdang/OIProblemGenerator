## Key Observations
1. **Suffix Tree vs Suffix Trie**: Suffix tree compresses chains of nodes with single children, reducing space from O(n²) to O(n).
2. **Implicit vs Explicit**: Add a unique terminal character (like '$') to convert implicit suffix tree to explicit one where all suffixes end at leaves.
3. **Suffix Links**: Critical for linear-time construction (Ukkonen). Link from node representing string `s` to node representing `s` without first character.
4. **Edge Labels**: Store as (start, end) indices into original string to avoid copying substrings.

## Optimizations
- **Ukkonen's Algorithm**: Builds in O(n) online, maintaining `(node, position)` for longest implicit suffix.
- **Reverse SAM Construction**: Build suffix tree by constructing SAM on reversed string; the parent tree is the suffix tree of original.
- **Alphabet Handling**: Use `map<char,int>` for large alphabets, array for small (e.g., 26 letters).

## Problem Transformations
1. **Longest Common Substring**: Build generalized suffix tree for multiple strings (with separators), find deepest node with leaves from all strings.
2. **Pattern Matching**: Walk down tree with pattern; if you can traverse entirely, pattern exists.
3. **Longest Repeated Substring**: Find node with maximum string depth and leaf count > 1.
4. **LCP Queries**: LCP of suffixes i and j = string depth of LCA of corresponding leaves.
5. **Cyclical Patterns**: For cyclic pattern matching (CF235C), slide window and use suffix links to remove first character efficiently.

## Implementation Notes
- Use `inf` for leaf edge lengths (extending to end of string).
- Suffix links from newly created internal nodes to previously created ones.
- During extension, handle three cases: follow existing edge, split edge, or create new leaf.
- The `rem` counter tracks how many suffixes still need to be inserted in current phase.