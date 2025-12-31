# 浅谈一些二分图匹配相关问题

**Author:** 柯绎思

## Key Ideas and Observations

### Greedy Matching for Intervals and Points (Problem 3.1)
- Sort intervals by right endpoint. For each interval, greedily assign the smallest available point within its range.
- **Correctness**: If an interval can match two points $ x_i < x_j $, then any future interval that can include $ x_i $ can also include $ x_j $. Hence, reserving larger points is better.

### Interval Containment Matching (Problem 3.2)
- Match smaller intervals into larger ones if fully contained.
- Greedy: sort outer intervals by right endpoint; for each, pick the unassigned inner interval with smallest left endpoint that fits.
- Similar reasoning as above — deferring use of “flexible” (wider or earlier-starting) intervals improves future options.

### Hall’s Theorem Application for Perfect Matching with One Missing Point (Problem 3.3)
- Given $ n-1 $ matched points and one new point $ y $, determine values of $ y $ such that perfect matching exists.
- Use modified greedy pass to find lower bound $ L $ and upper bound $ R $ on valid $ y $.
- Define $ F(l, r) = \#\{i : [l_i, r_i] \subseteq [l, r]\} - \#\{i : x_i \in [l, r]\} $. By Hall’s condition, need $ F(l, r) \leq 0 $ for all $ [l, r] $.
- After adding $ y $, this becomes $ F'(l, r) \leq 0 $. The feasible region for $ y $ is the intersection of all $ [l, r] $ where $ F(l, r) = 1 $, leading to bounds $ L, R $.

### Simplified Hall Condition When Right Endpoints Are Infinite (Problem 3.4)
- All constraints are of form $ x \geq l_i $.
- Maintain array where each $ l_i $ adds +1 on $[l_i, \infty)$, each $ x_i $ subtracts 1 on $[x_i, \infty)$.
- There exists perfect matching iff every prefix sum (from high to low) is non-negative.
- This reflects cumulative demand vs supply from left to right.

### Matroid Structure of Matchable Sets (Section 4)
- The family of subsets $ S \subseteq V_1 $ that admit a matching forms a matroid.
  - **Hereditary property**: Any subset of a matchable set is matchable.
  - **Exchange property**: If $ |S_2| > |S_1| $, then there exists $ x \in S_2 \setminus S_1 $ such that $ S_1 \cup \{x\} $ is matchable. Proved via alternating paths in symmetric difference of matchings.
- Enables greedy algorithms for weighted independent set (e.g., schedule tasks by descending profit).
- To maintain independence upon insertion: if insertion creates a circuit (unique cycle in matroid), remove the minimum-weight element in it.
- Deletion may allow reinsertion of one best candidate; use segment tree to track candidates based on value thresholds.

### Lexicographically Smallest Maximum Matching (Section 5)
- Goal: Find the lexicographically smallest set of vertices in $ V_1 $ covered by some maximum matching.
- Naive method: augment in increasing order of vertex index → gives desired result but slow.
- Faster approach uses recursion and minimum vertex cover:
  - Function `solve(S1, S2, S3)` computes optimal matching for $ V_1 = S1 \cup S2 $, $ V_2 = S3 $, assuming $ S2 $ must be included and has smaller indices than $ S1 $.
  - Split $ S1 $ into $ X $ (smaller half) and $ Y $ (larger half).
  - Compute min vertex cover $ C $ of subgraph $ (S2 \cup X, S3) $.
  - Partition nodes:
    - $ Bl = (S2 \cup X) \cap C $, $ Al = (S2 \cup X) \setminus Bl $
    - $ Ar = S3 \cap C $, $ Br = S3 \setminus Ar $
  - Key lemmas:
    - $ (Bl, Br) $ has a perfect matching of size $ |Bl| $.
    - $ Bl $ will remain matched even after adding $ Y $, due to higher indices.
    - Matching splits cleanly: $ (Al, Ar) $ and $ (Bl \cup Y, Br) $ become independent subproblems.
  - Recurse: `solve(Al ∩ S1, Al ∩ S2, Ar)` and `solve(Y, Bl, Br)`
- Time complexity: $ O(T \log |V1|) $, where $ T $ is time to compute minimum vertex cover.
- Minimum vertex cover in bipartite graphs can be derived from maximum matching via Konig’s theorem (complement of maximum independent set).