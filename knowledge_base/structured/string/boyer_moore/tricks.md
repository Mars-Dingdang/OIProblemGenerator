## Key Observations

1. **Bad Character Rule (Δ₁)**: When a mismatch occurs at position `j` in pattern and character `c` in text:
   - If `c` doesn't appear in pattern, shift pattern completely past `c` (shift = m)
   - Otherwise, align last occurrence of `c` in pattern with `c` in text
   - This allows skipping multiple characters at once

2. **Good Suffix Rule (Δ₂)**: When suffix of pattern matches but then mismatches:
   - Find rightmost occurrence of matched suffix in pattern with different preceding character
   - Shift pattern to align this occurrence
   - More complex but powerful for repetitive patterns

3. **Galil Optimization**: For multiple matches, after finding a match:
   - Compute shortest period `k` of pattern using prefix function
   - After match, only need to compare next `k` characters instead of full pattern
   - Prevents O(m*n) worst case for patterns like "AAA" in "AAAAA..."

## Common Optimizations

1. **Horspool Simplification**: Use only bad character rule with last character heuristic
2. **Sunday Algorithm (Quick Search)**: Look at character immediately after window
3. **Δ₀ Optimization**: Special handling for last character mismatch (80% of cases)
4. **Combined Shift**: Use `max(Δ₁, Δ₂)` for maximum skip

## Implementation Tricks

1. **Bad Character Table**: Use array of size 256 for ASCII, unordered_map for Unicode
2. **Good Suffix Preprocessing**: Can be computed in O(m) using suffix/preprocessing
3. **Memory vs Speed**: Bad character rule uses O(σ) memory, good suffix uses O(m)
4. **Real-world Performance**: Often sublinear (skips many characters)

## Problem Transformations

1. **Multiple Patterns**: Combine with Aho-Corasick
2. **Approximate Matching**: Adapt rules for edit distance
3. **Binary Data**: Works equally well on non-text data
4. **Case Insensitive**: Normalize case during preprocessing

## Edge Cases
- Empty pattern (matches everywhere)
- Pattern longer than text (no match)
- All identical characters (use Galil rule)
- No repeating characters (bad character rule optimal)