## Key Observations & Optimizations

### 1. Hash Function Design
- **Integer keys**: Use modulo a large prime number (e.g., 999997) to map large ranges to a fixed-size table.
- **String keys**: Convert to integer via polynomial rolling hash (e.g., base 127) and use unsigned long long natural overflow as modulo 2^64.
- **Negative keys**: Use `(key % M + M) % M` to ensure non-negative indices in C++.

### 2. Collision Resolution
- **Separate chaining (拉链法)**: Each bucket is a linked list. Simple, effective, and handles arbitrary load factors.
- **Open addressing (闭散列法)**: Store elements directly in the array, probing sequentially (linear probing) on collision. More cache-friendly but sensitive to clustering.

### 3. Reducing Collisions
- **Double hashing**: Use two independent hash functions (e.g., modulo two different large primes) for strings to drastically reduce collision probability.
- **Larger prime table size**: Choose a prime slightly larger than the expected number of elements to improve distribution.

### 4. Implementation Tricks
- **Pre-allocated arrays**: Use static arrays (like `data[SIZE]`) for speed, avoiding dynamic allocation per node.
- **Forward-star structure**: Store `next`, `key`, `value` in a struct array; `head` array points to the first index in each bucket.
- **Map-like interface**: Overload `operator[]` to allow `hash_map[key] = value` syntax, returning a reference for both insertion and modification.

### 5. Problem Transformations
- **Frequency counting**: Use hash table to count occurrences of elements (e.g., in array or string problems).
- **Two-sum / Pair finding**: Store seen values in a hash table to check for complements in O(1) time.
- **Deduplication**: Use hash table to maintain a set of unique items.
- **Caching intermediate results**: Memoize computed values (e.g., in dynamic programming) to avoid recomputation.

### 6. Performance Notes
- **Expected O(1)** operations assume a good hash function and reasonable load factor (e.g., N/M < 1).
- **Worst-case O(n)** occurs when many keys hash to the same bucket (e.g., adversarial inputs).
- **Memory vs. speed trade-off**: Larger tables reduce collisions but increase memory usage.

### 7. Advanced Variants
- **XOR linked list for chaining**: Uses XOR of addresses to store both next and prev pointers in one field, halving memory overhead for doubly-linked list buckets (mentioned in the text for linked lists, applicable here).
- **Cuckoo hashing**: Uses two hash functions and two tables, providing worst-case constant lookup time.
- **Robin Hood hashing**: A variant of open addressing that reduces variance in probe lengths.