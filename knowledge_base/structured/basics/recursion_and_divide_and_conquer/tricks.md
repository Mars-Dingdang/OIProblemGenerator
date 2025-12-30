**Key Observations & Optimizations:**
1.  **Trust the Recursive Leap**: Write a recursive function by defining its purpose clearly and trusting it works for smaller inputs. Don't mentally unroll the stack.
2.  **Base Case is Crucial**: Always define a simple, non-recursive terminating condition to prevent infinite recursion.
3.  **Divide and Conquer Pattern**: Decompose -> Solve (recursively) -> Combine. Works best when subproblems are independent (otherwise, use DP).
4.  **Tree Traversal Analogy**: Divide and conquer (like merge sort) is analogous to a **post-order traversal**: process left, process right, then handle current node (merge).
5.  **Avoiding Redundancy**: For overlapping subproblems, add **memoization** (caching results) to transform naive recursion into efficient DP.
6.  **Transformation Patterns**:
    -   **Path Sum Problem**: Count paths from a node by recursively asking: "Can I start a path here?" and "How many paths start from my children with the updated sum?"
    -   **Array Sorting**: Split array, sort halves recursively, merge.
    -   **Binary Search**: Narrow search range by half each step—a classic divide and conquer.
7.  **Stack Overflow Mitigation**: For deep recursion, consider:
    -   Converting to an iterative solution using an explicit stack.
    -   Ensuring the recursion depth is log(n) (like in balanced divide and conquer) rather than O(n).
    -   Tail recursion (if supported by compiler optimization).
8.  **Debugging Tip**: Visualize the recursion tree. The problem size should shrink towards the base case at each level.