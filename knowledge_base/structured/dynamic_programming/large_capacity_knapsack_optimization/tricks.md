# 浅谈 OI 中的大容量背包问题

**Author:** 方心童

## Key Ideas and Observations

### 1. **Greedy Lower Bound with Correction**
- Use a greedy selection by descending value-to-weight ratio to get an initial solution.
- Define `t_i` as the number of item `i` selected in this greedy scheme.
- Prove that there exists an optimal solution where each item `i` is taken at least `t_i - W^2 / w_i` times.
- This allows us to subtract a known base amount from each item's count, reducing the remaining volume to `O(nW^2)` instead of depending on M.

### 2. **Volume Reduction via Modular Arithmetic and Pigeonhole Principle**
- **Lemma 1 (Pigeonhole on Prefix Sums mod n)**: Any multiset of size `n` has a non-empty subsequence whose sum is divisible by `n`.
- Used to prove that over-selecting low-ratio items can be replaced with higher-ratio ones if their total weight forms a multiple of some `w_q`, leading to contradiction unless bounds are respected.

### 3. **Complete Knapsack Optimization**
- For complete knapsack, any optimal solution must have total weight > `M - W` (otherwise add one more item).
- Thus, only need to compute DP values in range `(M - W, M]`.
- Use **divide and conquer with (max, +) convolution**: 
  - Any selection set can be split into two parts differing by at most `W` in sum (proved via contradiction).
  - So `f[i]` depends on `[i/2 - W, i/2 + W]`, enabling recursive computation over `O(log M)` layers.
  - Base case: precompute up to `O(W)` using naive DP.
  - Total complexity: `O(W^2 log W)` due to `O(log M)` convolutions over `O(W)` windows.

- **Alternative approach using GCD and linear Diophantine equations**:
  - Theorem based on Frobenius number: Given weights `w_1,...,w_p`, the largest unrepresentable multiple of `g = gcd(w_1,...,w_p)` is bounded.
  - This implies that beyond a certain point, any large sum from later items can be replaced by earlier (better) items — so we limit how many high-index items we can take.
  - Specifically, for position `p`, the total volume from items after `p` is at most `⌊3W²/p⌋`.
  - Process items backwards, updating only first `O(W²/i)` states per item → total `O(Σ_{i=1}^W W²/i) = O(W² log W)`.

### 4. **Multiple Knapsack via Enhanced Binary Splitting**
- Standard binary splitting breaks `d` copies into powers of two → `O(log d)` items.
- Here, process all items grouped by power-of-two levels (`k`).
- Maintain DP state scaled by `2^k`: `f[i]` = max value with remaining volume `i * 2^k`.
- Transition from level `k` to `k-1`: scale down and update with items of size `2^{k-1}`.
- Crucially, for each `k`, the total contribution from smaller items is bounded → only need to keep `O(Σw_i)` states across transitions.
- Final complexity: `O(n Σw_i log W)`.

### 5. **Value-Domain Swapping and Greedy-Assisted Trimming**
- When `Σv_i` is small but `Σw_i` is large:
  - Swap state: let `f[i]` = minimum volume to achieve value `i * 2^k`.
  - Instead of binary searching on answer, use **greedy upper bound**:
    - Let `P` be value from greedy algorithm.
    - True answer `Q` satisfies `Q < P + V` (since leftover space < max weight, gain < max value).
  - So during transition, only maintain states in `[P / 2^k - 2Σv_i, (P + V)/2^k]`.
  - Achieves `O(n Σv_i log V)` without extra log factor from binary search.

### 6. **Tightness of Bounds**
- Show that `Ω(Σv_i)` states may be necessary → the state pruning is asymptotically optimal.

### 7. **Applications and Example Problems**
- Technique applied to ICPC Kunming 2024 problem: selecting exactly `n` items to reach volume `M`.
- Shift volumes by `B = floor(M/n)` to center around zero.
- Prove existence of ordering where partial sums stay within `[-n, n]` → use FFT-based convolution with divide-and-conquer over counts.