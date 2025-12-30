### Key Observations and Tricks

- **Indexing Trick**: Use 1-based indexing for binary heap in array form. For node at index `i`, left child is at `2*i`, right at `2*i+1`, and parent at `i/2`.

- **O(n) Heap Construction**: Instead of inserting elements one by one (which takes $ O(n \log n) $), initialize the entire array and run `down` from the last non-leaf node (index `n/2`) backwards to root. This exploits the fact that most subtrees are small, leading to an overall linear time complexity.

- **Upward vs Downward Adjustment**: 
  - Insertion uses `up()` — only path from leaf to root needs checking.
  - Deletion uses `down()` — only path from root to leaf may be affected.

- **Increase Key Efficiently**: To increase value at position `i`, update `h[i]` and call `up(i)` — works because increased value may violate heap property upward.

- **Decrease Key**: Update value and call `down(i)` to fix violations downward.

- **Application: Median Maintenance with Dual Heaps (对顶堆)**:
  - Maintain two heaps: a max-heap for the lower half and a min-heap for the upper half.
  - Balance sizes so that max-heap holds $\lfloor (n+1)/2 \rfloor$ elements.
  - Median is then always the top of the max-heap (for smaller median on even length).
  - Insert into appropriate heap, then rebalance sizes with at most one transfer.

- **Avoid Full Rebuilds**: After modifications, only adjust along the affected path rather than rebuilding whole heap.

- **Static Array Assumption**: The standard implementation assumes static maximum size. For dynamic allocation, use `std::vector` and maintain logical size `n`.