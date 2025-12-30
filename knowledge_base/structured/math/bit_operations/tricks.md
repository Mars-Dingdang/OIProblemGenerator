## Key Observations

1. **Fast arithmetic**:
   - Multiply by 2ⁿ: `x << n`
   - Divide by 2ⁿ: `x >> n` (note: negative numbers round toward -∞, not 0)
   - Modulo 2ⁿ: `x & ((1 << n) - 1)`

2. **Bitmask techniques**:
   - Enumerate all subsets of mask `m`: `for (int s = m; s; s = (s - 1) & m)`
   - Check if `x` is subset of `y`: `(x & y) == x`
   - Toggle bits in range: `x ^= ((1 << (r+1)) - (1 << l))`

3. **Lowbit patterns**:
   - `x & -x` isolates lowest set bit
   - `x & (x - 1)` clears lowest set bit
   - `x | (x + 1)` sets lowest unset bit

4. **Useful identities**:
   - `a ^ b ^ b = a` (XOR cancellation)
   - `a + b = (a ^ b) + ((a & b) << 1)` (addition via bits)
   - `-x = ~x + 1` (two's complement)

5. **Conditional operations (branchless)**:
   - Max: `x ^ ((x ^ y) & -(x < y))`
   - Min: `y ^ ((x ^ y) & -(x < y))`
   - Absolute: `(x + (x >> 31)) ^ (x >> 31)` for 32-bit

6. **Power of two checks**:
   - `x > 0 && (x & (x - 1)) == 0`
   - Next power of two: `1 << (32 - __builtin_clz(x - 1))`

7. **Bit reversal patterns**:
   - Reverse 8-bit: `((x * 0x0202020202ULL) & 0x010884422010ULL) % 1023`
   - Reverse 32-bit via divide-and-conquer

8. **GCC builtins (fast)**:
   - `__builtin_popcount(x)` - count set bits
   - `__builtin_ctz(x)` - count trailing zeros
   - `__builtin_clz(x)` - count leading zeros
   - `__builtin_ffs(x)` - find first set bit (1-indexed)

9. **Parity tricks**:
   - XOR all bits: `x ^= x >> 16; x ^= x >> 8; x ^= x >> 4; x ^= x >> 2; x ^= x >> 1; x &= 1;`
   - Or use `__builtin_parity(x)`

10. **Gray code**:
    - Convert to Gray: `x ^ (x >> 1)`
    - Convert from Gray: `for (mask = n >> 1; mask; mask >>= 1) n ^= mask;`

## Common Problem Transformations

1. **Subset enumeration**: Represent sets as bitmasks, iterate over subsets efficiently.
2. **State compression**: Use bits to represent boolean states in DP.
3. **Fenwick tree operations**: Rely heavily on lowbit.
4. **Sieve optimizations**: Use bitset for prime sieves to save memory.
5. **Game theory**: Nim games use XOR of pile sizes.
6. **Graph algorithms**: Adjacency matrices for small graphs can be bitmasks.

## Warnings
- Right shift on signed integers is implementation-defined (usually arithmetic shift).
- Left shift of negative numbers is undefined behavior.
- Shifting by ≥ bit width is undefined.
- Bitwise operations on floating-point require type punning (not recommended).