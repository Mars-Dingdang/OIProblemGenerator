# 后缀树的构建

**Author:** 代晨昕

### Key Ideas and Observations

- **Suffix Tree vs Suffix Trie**: A suffix trie contains all suffixes explicitly but uses O(n²) space. The suffix tree compresses non-branching paths into single edges, reducing space to O(n).

- **Implicit Suffix Tree**: This is a compressed version of the suffix trie that only includes branching nodes and leaves. It may not represent all suffixes as explicit leaves until a unique terminal symbol is added.

- **Reverse Construction via Suffix Automaton**: 
  - The parent tree of a suffix automaton of the reversed string corresponds to the suffix tree of the original string.
  - Incrementally adding characters from back to front allows building the suffix tree using techniques similar to SAM construction.
  - Uses `trans` transitions (like SAM transitions) and splits nodes when necessary to maintain correctness.
  - Employs amortized analysis with depth-based potential function to prove O(n) total time.

- **Ukkonen’s Algorithm (Forward Construction)**:
  - Builds implicit suffix tree incrementally by appending characters at the end.
  - Maintains `(active, remain)` pointer indicating the current longest implicit suffix position in the tree.
  - Uses **suffix links** (`Link[x]`) to efficiently navigate from a node representing string `s` to the node representing `s[1:]`, enabling fast updates during extension.
  - When inserting a new character:
    - If transition exists, just update `remain`.
    - Otherwise, split edge or create new leaf, then traverse suffix links to process shorter suffixes.
  - Amortized O(1) per operation due to bounded number of iterations over total `remain` increases.

- **Bidirectional Dynamic Maintenance**:
  - Combines both methods to support insertions at both ends.
  - Maintain both `trans` and `Link` structures simultaneously.
  - Special handling for the active region around `(active, remain)` where `leftpos'` sets may differ due to boundary effects.
  - On front insertion, use reverse-style node splitting; on end insertion, use Ukkonen-style expansion.
  - Transfer edge updates during splits are localized and can be tracked via traversal from linked ancestors.

- **Efficient Applications**:
  - Sliding window substring counting: Maintain suffix tree with Ukkonen while removing oldest character via leaf deletion and possible compression.
  - Real-time distinct substring count with double-ended queue operations: Achieve linear total complexity by combining both constructions.

- **Amortization Tricks**:
  - In Ukkonen: Total work bounded by total increase in `remain`, which is O(n).
  - In reverse method: Potential function based on depth ensures expensive redirection steps are paid off by previous depth gains.

- **Edge Case Handling**:
  - Only one node (the active one) might have ambiguous `trans` behavior due to inclusion/exclusion of boundary positions in `leftpos'`.
  - Terminal sentinel (e.g., `#`) ensures all suffixes become explicit leaves in final suffix tree.