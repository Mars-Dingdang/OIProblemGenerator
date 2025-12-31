# 《拼数》命题报告

**Author:** 姜迅驰

### Key Observations and Tricks

#### **Lexicographic Minimization via Infinite String Comparison**
- To minimize the concatenated string `S`, we sort numbers `i` from 1 to `n` by the lexicographic order of the infinite repetition of their binary representation: `f(i)∞`.
- **Key Lemma**: For two strings `X` and `Y`, if `X∞ < Y∞`, then `X + Y < Y + X`. This allows us to define a total order for sorting.
- If `X∞ = Y∞`, then `X + Y = Y + X`, so ordering between them doesn't matter.
- Thus, the optimal permutation sorts `i` by `f(i)∞` ascending.

#### **Efficient Comparison Using Finite Prefixes**
- Comparing `f(i)∞` and `f(j)∞` infinitely is impossible, but **Theorem 2** shows: 
  > The first difference between `X∞` and `Y∞` occurs within the first `2 * max(|X|, |Y|)` characters.
- So we only need to compare prefixes of length up to `2N` (where `N = |f(n)|`) to decide the order.

#### **Finding the Critical Number `c`**
- Let `P` be the sorted permutation. We want the first `k` bits of the concatenated string.
- Find the unique `c` such that the cumulative length of `f(P₁)` through `f(P_{Q_c - 1})` ≤ `k`, but including `f(c)` exceeds it.
- So `f(c)` is partially included — only a prefix contributes.

#### **Computing Contributions Efficiently**
- **Idea**: Instead of building the entire string, compute how many complete numbers fit in the first `k` bits, and handle the partial one.
- Define `g(i, c)` = the largest number with binary length `i` that appears before `c` in the permutation.
- Since numbers are sorted by `f(i)∞`, all numbers of the same bit-length appear in increasing order.
- Use a candidate prefix `T = f(c)∞[1..2N]` to estimate `g(i, c)` as either `h(T[1..i])` or `h(T[1..i]) - 1`, then verify using lexicographic comparison.

#### **Digit DP-like Contribution Counting**
- For each bit-length `i`, count the number of 1s in all numbers from `2^{i-1}` to `g(i, c)`.
- This is done by iterating over positions where a digit becomes 1, and computing contributions:
  - Fixed prefix part: add `x × 2^{i−j}` for fixed higher bits.
  - Variable suffix part: `[0, 2^{i−j})` has `(i−j) × 2^{i−j−1}` ones.
- Implemented efficiently using base-2^k high-precision arithmetic to avoid slow big integer operations.

#### **Avoiding Binary Search:逐位确定 (Bit-by-bit Determination)**
- Early algorithms used binary search on `c`, costing `O(N⁴)`.
- **Optimization**: Instead, determine `g(N−1, c)` bit-by-bit from high to low.
- Maintain current candidate `x` and total length `len` contributed by all numbers ≤ `x` in the order.
- When flipping a bit in `x`, update `g(i, x)` and adjust `len` accordingly.
- Changes in `g(i, x)` depend on whether the prefix changed and whether `d_i` (a correction term) flips.

#### **Efficient Maintenance with Block Processing**
- To maintain `d_i`, which depends on whether `f(x)[1..i]∞` matches a shifted version, we track a boolean array `r_j = [f(x)∞[j] == f(x)∞[j+i]]`.
- Only first `2(N−1)` entries matter (by Theorem 2).
- Update `r` in `O(1)` per bit flip in `x`, since changing one bit affects at most 4 positions in `f(x)∞`, hence 4 in `r`.
- Use **block optimization** (size 64) with `unsigned long long` to quickly find the first `0` in `r` → gives `d_i`.
- Enables `O(N)` updates when modifying a bit of `x`.

#### **Final Complexity**
- Total of `O(N)` bit-determination steps, each taking `O(N)` → overall `O(N²)`.
- All other parts (computing contributions, handling partial number) also bounded by `O(N²)`.

### Summary of Innovation
- Combines string theory, lexicographic ordering, high-precision arithmetic, and clever data structure optimizations (bit manipulation + block scanning) to solve what seems like a brute-force problem efficiently.
- Avoids explicit enumeration via mathematical insights about infinite periodic strings.