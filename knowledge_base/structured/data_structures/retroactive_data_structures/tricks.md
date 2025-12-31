# 浅谈可追溯化数据结构

**Author:** 孔朝哲

### Key Ideas and Observations

- **Partial vs Full Retroactivity**:
  - *Partial*: Only supports querying the final state after modifying the operation history.
  - *Full*: Supports querying the state at any time t, requiring more sophisticated bookkeeping.

- **Commutativity Helps**: For union-find, union operations are commutative, so partial retroactivity is straightforward—just apply all unions. For full retroactivity, use Link-Cut Trees (LCT) to maintain a minimum spanning tree over time, enabling dynamic connectivity queries at any moment.

- **Queue Retroactivity**:
  - Operations can be reordered: all `enqueue` operations can be processed first, then `dequeue`. This allows maintaining only the order of enqueues via a linked list.
  - Use two pointers (`F`, `B`) for front and back. Insertions and deletions update these pointers based on position relative to F/B.
  - For full retroactivity, separate enqueue and dequeue operations into two balanced BSTs (`Te`, `Td`). To query `front(t)`, count deqeueues before t, say k, then find the (k+1)-th enqueue in `Te`.

- **Stack Retroactivity**:
  - An element is on top at time t iff the number of pushes minus pops in (t', t] is zero, and the last operation is a push.
  - Model each `push` as +1, `pop` as -1. Find the last operation where the suffix sum from that point is exactly 1.
  - Maintain a balanced BST keyed by time, storing subtree min/max suffix sums and total sum. Enables binary search for the correct push operation.

- **Deque Retroactivity**:
  - Cannot simply split into two stacks due to cross-side interference (e.g., popping from empty side affects the other).
  - Instead, simulate a manual deque using array indices `L` and `R`. Each `pushL`/`popL` affects `L`, similarly for right.
  - Maintain two balanced trees `Tl` and `Tr` tracking net changes to `L` and `R`. Prefix sum gives current index.
  - Value at position i comes from the latest `pushL(x)` that set `L=i` or `pushR(x)` that set `R=i`. Found via suffix sum queries on operation trees.

- **Priority Queue (Partial)**:
  - Maintain `Qnow`: current elements in heap.
  - Use concept of *bridge* times t where `Qt ⊆ Qnow`.
  - Assign weights to operations: insert(k ∈ Qnow) → 0, insert(k < Qnow) → +1, delete_min → -1. Bridges occur when prefix sum is 0.
  - On insertion at time t, find nearest bridge before t to determine which elements were deleted after t; this helps compute what new elements enter `Qnow`.
  - Use auxiliary balanced BSTs to store metadata like max{k' < Qnow} and min{k' ∈ Qnow} in subtrees.

- **Priority Queue (Full) – Hierarchical Checkpointing**:
  - Use a scapegoat tree over the operation timeline. Each node represents a block of operations.
  - In each node, maintain a *partially retroactive* priority queue (with `Qnow` and `Qdel` sets).
  - Insertion propagates up ancestors; if imbalance occurs, reconstruct subtree.
  - Query at time t requires merging O(log m) partial structures from disjoint intervals covering [0, t].
  - Merging two structures:
    - $ Q_{3,\text{now}} = Q_{2,\text{now}} \cup \text{max-A}(Q_{1,\text{now}} \cup Q_{2,\text{del}}) $
    - $ Q_{3,\text{del}} = Q_{1,\text{del}} \cup \text{min-D}(Q_{1,\text{now}} \cup Q_{2,\text{del}}) $
    - Where A = |Q1.now|, D = |Q2.del|, and max-A(S) takes top A elements.
  - Represent `Qnow` and `Qdel` as unions of small number of balanced trees (called *mergeable partial retroactive heaps*) to keep representation compact.
  - Final merge of k structures uses divide-and-conquer with linear number of trees (O(k)), leading to O(k log k log m) merge time.
  - Query complexity: O(log²m log log m); update: amortized O(log²m) due to scapegoat reconstruction cost.

- **General Insight**:
  - Many data structures benefit from decomposing operations and analyzing their algebraic properties (commutativity, invertibility).
  - Balanced BSTs are central tools for maintaining temporal order and answering rank/select queries efficiently.
  - Scapegoat trees enable clean lazy rebuilding for global reconstruction without rotations.