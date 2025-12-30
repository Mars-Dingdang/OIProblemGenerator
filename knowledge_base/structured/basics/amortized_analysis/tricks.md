## Key Observations
- **Aggregate Analysis**: For a sequence of n operations, total cost is O(n), giving O(1) amortized per operation.
- **Accounting Method**: Assign extra "credit" to cheap operations (e.g., push) to pay for expensive ones (e.g., multi-pop). Each push stores 1 credit for future pop/multi-pop.
- **Potential Method**: Define a potential function Φ (e.g., stack size). Amortized cost = actual cost + ΔΦ. For stack, Φ = |S|, push amortized cost = 2, pop/multi-pop = 0.

## Common Optimizations
- **Lazy Operations**: Delay expensive operations until necessary (e.g., dynamic array resizing).
- **Charge to Future**: Prepay costs during simple operations to cover later complex ones.

## Problem Transformation Patterns
- **Sequence Analysis**: When worst-case per operation is high but sequence total is bounded, consider amortized analysis.
- **Data Structure Design**: Use amortized analysis to justify operations like resizing vectors, splay tree rotations, union-find path compression.