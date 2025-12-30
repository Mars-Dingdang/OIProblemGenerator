- **Core Idea**: The state of the outer DP is itself a configuration of an inner DP or a predicate. We model the inner condition as an automaton (often a DFA), and the outer DP counts sequences that drive this automaton.
- **Automaton Construction**: The inner DP's state space (which may be huge) is compressed into an automaton. This is done by treating the inner DP's state vector as a node, and transitions are defined by how the state updates with new input.
- **DFA Minimization**: After constructing the automaton, apply DFA minimization (e.g., Hopcroft's algorithm) to reduce the number of states, which is crucial for efficiency.
- **Common Patterns**:
  - Counting sequences where a certain property (like LCS with a fixed string, or matching a pattern) holds. The inner DP computes the property (e.g., LCS values), and the outer DP enumerates sequences.
  - Problems where the state is a "profile" of a combinatorial object (e.g., a mask of conditions).
- **Implementation Steps**:
  1. Define the inner DP state and its transitions for a single character/addition.
  2. Perform a BFS/DFS to generate all reachable inner states from the start state; each unique state becomes an automaton node.
  3. For each node and each possible input, compute the next inner state (by simulating the inner DP transition) and add an edge.
  4. Minimize the automaton (optional but often needed).
  5. Run the outer DP on the automaton: dp[i][state] = ways to be in that state after i steps.
- **Optimizations**:
  - Use hashing (e.g., vector to int) to represent inner states compactly.
  - Prune unreachable states early.
  - If the inner DP state is small (e.g., a mask), enumeration is straightforward.
- **Example Problems**:
  - **Hero meet devil**: Count strings of length n whose LCS with a given string S is a specific value. Inner DP is the LCS DP row, outer DP enumerates strings.
  - **[TJOI2018] 游园会**: Count strings avoiding "NOI" patterns while matching LCS with another string.
  - **[NOI2022] 移除石子**: Complex condition on removals; inner state captures game status.
- **Key Observation**: The outer DP's state space is the set of inner DP states, not the raw input. This transforms a double DP into a single DP on an automaton, often reducing complexity.