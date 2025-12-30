## Key Observations & Tricks

### 1. Set Operations via Bitwise Operations
- **Intersection**: `a & b`
- **Union**: `a | b`
- **Complement**: `~a` (assuming infinite bits, but in practice use mask for limited universe)
- **Set Difference**: `a & (~b)`
- **Symmetric Difference**: `a ^ b`

### 2. Modulo Power of Two
- `x % (2^k) == x & ((1 << k) - 1)`
- This is because `2^k` in binary is `1` followed by `k` zeros, so `2^k - 1` is `k` ones
- Much faster than modulo operation

### 3. Power of Two Detection
- `n > 0 && (n & (n - 1)) == 0`
- Works because subtracting 1 from a power of two flips all lower bits to 1
- The AND operation clears the only set bit

### 4. Removing Lowest Set Bit
- `n & (n - 1)` removes the lowest set bit
- Useful for counting set bits or processing bits from LSB to MSB

### 5. Subset Iteration Pattern
- **Key formula**: `s = (s - 1) & m` iterates through all subsets of `m` in decreasing order
- **Complexity**: O(2^popcount(m)) where popcount is number of set bits
- **Includes empty subset**: Use do-while loop with termination condition `s != m`

### 6. All Submasks Iteration
- Double loop over all masks and their submasks takes O(3^n) time
- **Proof**: Each bit has 3 states (0 in both, 1 in mask only, 1 in both)
- Essential for many bitmask DP problems

### 7. Common Transformations
- **Enumerate subsets of fixed size**: Use Gosper's Hack
- **Iterate supersets**: Similar pattern with `s = (s + 1) | m` or variations
- **SOS DP**: Sum over subsets/supersets for optimization
- **Bitmask DP**: Represent states as bitmasks, transition using subset iteration

### 8. Practical Tips
- Use `__builtin_popcount()` for GCC/Clang to count set bits
- Use `1LL << k` for shifts when k ≥ 32 to avoid overflow
- Remember that bit indices usually start from 0 (LSB)
- When complementing, mask with `(1 << n) - 1` to limit to n-bit universe