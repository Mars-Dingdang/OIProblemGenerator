# 《太阳神的宴会》命题报告

**Author:** 陈雨昕

### Key Ideas and Observations

- **Similarity as an Equivalence Relation**: String similarity via permutation is proven to be an equivalence relation (reflexive, symmetric, transitive). This allows grouping strings into equivalence classes.

- **Shape Sequences**: A string is mapped to a shape sequence that captures the pattern of character appearances without depending on specific characters:
  - `a_i = 0` if character `s_i` appears for the first time.
  - Otherwise, `a_i = x`, where `x` is the rank (from largest to smallest) of the last occurrence position of the character equal to `s_i` in the prefix `s[1..i-1]`.
  - Two strings are similar iff their shape sequences are identical.

- **Subshape Sequence**: For a shape sequence `a`, the subshape over interval `[l, r]` simulates how a substring's shape would look, adjusting indices based on local context (resetting to 0 when referencing characters not present in the substring).

- **Counting Strings per Shape**: A shape sequence with `z` zeros corresponds to exactly `A_k^z = k! / (k-z)!` distinct strings, due to choosing `z` distinct characters from `k` and assigning them according to appearance order.

- **Subshape Automaton**: Inspired by suffix automata, this automaton accepts all subshape sequences of a given shape sequence. It uses state `(E, z)` where:
  - `E` is an equivalence class of substrings with the same right-end positions (`RA(B)`),
  - `z` is the number of distinct characters (number of zeros) in the represented strings.
  - The automaton has `O(k|A|)` states and transitions, built incrementally using parent links and split operations analogous to SAM.

- **Efficient Construction**: The automaton is constructed online by extending the shape sequence character-by-character. Transitions use `tr(q, a)` which maps `a` to 0 if it exceeds the current number of distinct characters.

- **Merging Identical Transitions**: Further optimization observes that transitions depend only on the equivalence class `E` and whether `a=0`. Thus, only `δ(q, 0)` needs explicit storage; others follow uniformly, reducing space to `O(k|A|)`.

- **Dynamic Programming over Weighted DAG**: To solve the full problem with multiple strings:
  - Build subshape automata for each string’s shape sequence.
  - Combine them recursively: for each string `S_i`, after matching the longest valid prefix in its automaton, pass the remainder to the next stage (`i+1`).
  - Model this as a weighted DAG where edge weights account for the number of actual strings corresponding to transitions (e.g., weight `k - z_q` for new character introduction).
  - Use DP to sum path weights from start to end, avoiding explicit construction through contribution aggregation using suffix sums over equivalent states.

- **Generalization**: The method applies to any equivalence relation induced by an automaton transformation `M: Σ* → Σ'∗` where `s ∼ t ⇔ M(s) = M(t)`, and suffixes fall into `K` classes per state. Examples include ordering patterns or normalized GCD sequences.