# 浅谈支配树及其应用

**Author:** 陈孙立

### Key Ideas and Observations

- **Dominance Definition**: In a directed graph with source $ s $, $ x $ dominates $ y $ iff every $ s \to y $ path goes through $ x $. The relation is transitive, antisymmetric, and for any $ z $, all dominators of $ z $ form a total order under dominance.

- **Immediate Dominator (idom)**: For $ x \neq s $, $ \text{idom}(x) $ is the unique dominator such that any other dominator of $ x $ also dominates $ \text{idom}(x) $. The dominator tree connects $ \text{idom}(x) \to x $.

- **Dominator Tree Property**: $ x $ dominates $ y $ iff $ x $ is an ancestor of $ y $ in the dominator tree.

- **Semi-Dominator (sdom)**: A key intermediate concept. $ \text{sdom}(x) $ is the smallest (by DFS number) node $ y $ such that there exists a path $ y = v_0, v_1, \ldots, v_k = x $ where all internal nodes $ v_i > x $ in DFS order. This helps compute $ \text{idom}(x) $.

- **Key Lemmas**:
  - $ \text{idom}(x) $ lies on the DFS tree path from root to $ x $, and $ \text{idom}(x) $ is an ancestor of $ \text{sdom}(x) $.
  - $ \text{sdom}(x) $ can be computed from incoming edges: either directly via $ (v,x) $, or indirectly via $ \text{sdom}(u) $ where $ u $ is an ancestor of $ v $ and $ (v,x) $ exists with $ v > x $.

- **Computing sdom**: Process nodes in reverse DFS order. Use a union-find-like structure to maintain minimum $ \text{sdom} $ value along the current DFS tree path. For each node $ w $, candidates for $ \text{sdom}(w) $ come from:
  1. Direct predecessors $ v $ (i.e., $ (v,w) \in E $)
  2. $ \text{sdom}(u) $ where $ u $ is a proper ancestor of $ v $ in DFS tree and $ (v,w) \in E $, $ v > w $

  To efficiently get the second type, use a DSU that supports path queries to the root (minimum $ \text{sdom} $ along ancestors).

- **Pivot Node**: Define $ \text{pivot}(w) $ as the node on the DFS tree path from $ \text{sdom}(w) $ to $ w $ (excluding $ \text{sdom}(w) $) with minimal $ \text{sdom} $ value.

- **Final idom Calculation**:
  - If $ \text{sdom}(\text{pivot}(w)) = \text{sdom}(w) $, then $ \text{idom}(w) = \text{sdom}(w) $
  - Else, $ \text{idom}(w) = \text{idom}(\text{pivot}(w)) $

- **Bucket Technique**: During sdom computation, maintain buckets $ \text{bucket}[x] $ storing all $ w $ such that $ \text{sdom}(w) = x $. When marking $ x $, resolve all $ w \in \text{bucket}[x] $ by computing their pivot values using the DSU.

- **Applications**:
  - **Point domination set**: The common dominators of a set $ S $ are the ancestors of $ \text{LCA}_{\text{dom}}(S) $ in the dominator tree.
  - **Dominating edges**: Can be reduced to node domination by splitting edges into auxiliary nodes, or optimized without explicit construction using modified sdom logic.
  - **Strong articulation points and bridges**: A node $ v $ is a strong articulation point iff removing it increases the number of strongly connected components. This happens iff there exist $ x,y $ such that all $ x \to y $ or $ y \to x $ paths go through $ v $. Solved by building dominator trees from $ v $ and in the reverse graph.

- **Industrial Uses**: Applied in compiler optimization (control flow), neural network scheduling (identify frequently used nodes), and memory leak detection.