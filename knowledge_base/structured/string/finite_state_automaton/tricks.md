# 浅谈有限状态自动机及其应用

**Author:** 徐哲安

## Key Ideas and Tricks

### 1. **DFA vs NFA and Equivalence**
- **DFA**: Deterministic transitions; each state has exactly one next state per character.
- **NFA**: Non-deterministic with ε-transitions allowed; multiple next states possible.
- **Equivalence**: Every NFA can be converted to an equivalent DFA via **powerset construction**, though the state count may grow exponentially (up to $2^n$).
- Despite this, NFAs are useful for compact representation.

### 2. **Efficient NFA Simulation**
- **Naive**: $O(ns^2)$ due to tracking all active states.
- **Optimization with Bitset**: Represent state sets as bitmasks. Precompute transition masks for each state and character. Transition becomes bitwise OR of masks → complexity reduced to $O(ns^2 / \omega)$.
- **Method of Four Russians**:
  - Partition NFA states into blocks of size $T = O(\log n)$.
  - Preprocess all $2^T$ possible state subsets and their transitions under each character.
  - During simulation, use lookup tables to compute block transitions in bulk.
  - Achieves $O(ns^2 / (\omega \cdot \log n))$ time.

### 3. **Regular Expressions to NFA (Thompson’s Construction)**
- Recursive construction from regex syntax tree.
- Each operator (concatenation, union, Kleene star) adds constant-sized structure with ε-edges.
- Resulting NFA has $O(s)$ states and transitions for regex length $s$.
- Enables regex matching via NFA simulation in $O(ns)$ time without full DFA conversion.

### 4. **DFA Minimization**
- **Myhill-Nerode Theorem**: Minimal DFA corresponds to equivalence classes of strings under indistinguishability w.r.t. the language.
- Two states are equivalent if no suffix distinguishes them.
- **Partition Refinement Algorithm**:
  - Start with accepting vs non-accepting states.
  - Iteratively split classes if transitions lead to different current classes.
  - Time: $O(n^2 |\Sigma|)$.
- **Hopcroft’s Algorithm**:
  - More efficient partition refinement.
  - Maintain a worklist of “splitter” sets.
  - Only process splits that refine existing partitions.
  - Complexity: $O(n |\Sigma| \log n)$, average-case better.

### 5. **Applications in Competitive Programming**

#### **DP over Automaton States (DP on DFA)**
- When valid strings form a regular language, design a DFA capturing necessary state information (e.g., modulo values, rankings, bounded DP states).
- Use DP where state = current automaton state, transition = input digit/char.
- Example: Count substrings that represent “good numbers” by maintaining rank mod 11.

#### **DP over DP (DP套DP)**
- Inner DP checks condition (e.g., palindrome partitioning), outer DP counts inputs leading to success.
- Since inner DP state space is finite or bounded, it induces a regular language → modelable by DFA.
- Allows compression of complex state into automaton states.

#### **State Compression via Minimization**
- In problems like `f(n)` = min absolute sum after inserting ± between digits,
  - Naive DP state: achievable sums (unbounded).
  - Key insight: only need to track sums up to threshold ($w^2 - 1$).
  - Enumerate reachable bitsets → treat each as a state → minimize resulting DFA.
  - Final minimized automaton has far fewer states (e.g., 715 instead of thousands), enabling fast digit DP.

#### **Constructing DFA via Myhill-Nerode**
- For hard string reduction rules (e.g., median replace), define equivalence: $x \equiv y$ iff $\forall z$, $xz$ is good ⇔ $yz$ is good.
- Use BFS to generate shortest representative strings per class.
- Validate convergence: build DFAs for increasing lengths; stop when they stabilize.

#### **Suffix Structures as Minimized Tries**
- Suffix automaton = minimized suffix trie.
- Understanding via DFA theory clarifies properties: linear size, suffix links as failure transitions.

#### **Fast Regular Expression Matching**
- Standard method: Thompson NFA + simulation → $O(ns)$.
- Optimized: Use Method of Four Russians on expression tree.
  - Divide tree into $O(s / \log n)$ blocks.
  - Preprocess transitions within blocks.
  - Achieve $O(ns / \log n)$ matching time.
- Applied to counting prefixes with suffix matching regex.