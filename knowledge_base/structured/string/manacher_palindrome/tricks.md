# 浅谈回文子串问题

**Author:** 徐毅

### Key Ideas and Observations

- **String Transformation**: To unify the treatment of odd and even length palindromes, the input string is transformed by inserting a special character (e.g., `#`) between every pair of characters, and adding distinct boundary markers (e.g., `$` at the start and `@` at the end). This ensures all palindromes are treated as odd-length in the new string.

- **Manacher Algorithm Core Insight**: The algorithm uses symmetry around previously computed palindromes to avoid redundant comparisons. Two auxiliary variables are maintained:
  - `p`: the center of the rightmost palindrome found so far.
  - `mx`: the rightmost boundary (`i + R[i]`) of that palindrome.

- **Three Cases When Computing `R[i]`**:
  1. If `i >= mx`, no useful information from prior computation is available; initialize `R[i] = 1` and expand naively.
  2. If `mx > i` and `mx - i > R[j]` where `j = 2p - i` (the mirror of `i` about `p`), then due to symmetry, `R[i] = R[j]` because the palindrome at `j` lies entirely within the current rightmost palindrome.
  3. If `mx > i` and `mx - i <= R[j]`, then the palindrome at `i` can extend at least to `mx`, so set `R[i] = mx - i`, but further expansion may be needed.

- **Linear Time Justification**: Each successful character match during expansion increases `mx` by one. Since `mx` only moves forward and never exceeds the string length `n`, the total number of expansions is bounded by `O(n)`.

- **Efficient Updates**: After setting a lower bound for `R[i]`, the algorithm performs direct comparison beyond that bound until mismatch. Then it updates `p` and `mx` if the new palindrome extends past the old `mx`.

- **Applications Beyond Radius Calculation**:
  - **Counting Palindromes**: Using difference arrays to count occurrences of palindromes of specific lengths.
  - **Complementary Counting**: For counting intersecting palindromic pairs, use total pairs minus non-intersecting pairs.
  - **Union-Find Optimization**: In problems requiring nearest valid centers (e.g., double palindromes), maintain candidate positions with Union-Find to efficiently delete unusable ones.
  - **KMP Preprocessing**: For encrypted password recovery, preprocess reversed suffix matches using KMP failure function to quickly find maximal prefix-suffix overlaps.
  - **O(n) Distinct Palindromic Substrings**: A crucial theoretical result: any string has only `O(n)` distinct palindromic substrings, provable via the fact that each contributes to an increase in `mx` during Manacher's execution.
  - **Equivalence Relations**: Representing palindrome equivalence through equality and inequality constraints derived from Manacher’s process, forming a graph solvable via coloring under special structural properties (e.g., chordal-like constraints ensuring efficient counting).

- **Proof Sketch for O(n) Distinct Palindromes**: Only when `mx` increases does a new unique palindromic substring appear. Since `mx` increases at most `n` times, there are at most `O(n)` distinct palindromic substrings.

- **Handling Complex Constraints**: Many advanced problems reduce to enumerating centers or split points and applying data structures (prefix sums, DSU, hashing) to satisfy additional conditions while leveraging precomputed radii.