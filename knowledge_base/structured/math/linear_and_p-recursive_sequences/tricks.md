# 两类递推数列的性质和应用

**Author:** 钟子谦

### Key Ideas and Tricks

#### **Linear Recurrence Sequences**
- **Definition via Generating Functions**: A sequence is linearly recurrent if its generating function is rational: $ A(x) = S(x)/R(x) $ with $ R(0) = 1 $.
- **Berlekamp-Massey Algorithm**: Efficiently computes the shortest linear recurrence for a finite sequence in $ O(n^2) $. The key idea is incremental construction: maintain the shortest recurrence for each prefix, and update only when a discrepancy occurs. The update uses the most recent position where the recurrence length increased.
- **Cayley-Hamilton Theorem**: Any matrix power sequence $ \{I, M, M^2, \dots\} $ satisfies a linear recurrence of order at most $ n $ (matrix size), due to its characteristic polynomial annihilating $ M $.
- **Schwartz-Zippel for Vector/Matrix Sequences**: To find recurrence of vector/matrix sequences, randomly project to scalar sequences using random vectors. With high probability, the recurrence is preserved.

#### **Applications of Linear Recurrences**
- **Matrix Minimal Polynomial**: Equals the shortest linear recurrence of $ \{uM^kv\} $ for random vectors $ u, v $. Computed via Berlekamp-Massey on $ O(n) $ terms.
- **Optimizing DP**: If $ F(n) = F(0) \cdot C^n $, then $ \{F(n)\} $ is linearly recurrent. Use Berlekamp-Massey to find recurrence from first $ O(m) $ terms, then fast evaluate $ F(n) $ in $ O(m \log m \log n) $ instead of $ O(m^3 \log n) $.
- **Solving Sparse Linear Systems**: For $ Ax = b $, compute recurrence of $ \{A^k b\} $, then express $ x = A^{-1}b $ as a linear combination of $ b, Ab, \dots, A^{m-1}b $.
- **Sparse Determinant & Rank**: Multiply by random diagonal matrices to ensure minimal polynomial equals characteristic polynomial (w.h.p.), then extract determinant (constant term) or rank (degree after removing zero eigenvalues).

#### **P-Recursive (Integer Recursive) Sequences**
- **Definition**: Satisfy $ \sum_{k=0}^m P_k(n) a_{n-k} = 0 $, where $ P_k $ are polynomials. Equivalent to D-finite generating functions: $ \sum Q_i(x) A^{(i)}(x) = 0 $.
- **Algebraic Implies D-finite**: If a generating function is algebraic (satisfies polynomial equation), it is D-finite. Composition of D-finite with algebraic function remains D-finite under conditions.
- **Closure Properties**: Closed under addition, multiplication, convolution, shifting — similar to linear recurrences but more general.

#### **Algorithms for P-Recurrence**
- **Finding Recurrence**: Assume degree $ d $ and order $ m $, set up linear system from initial terms. Solve for coefficients of polynomial recurrence. Randomization ensures correct solution w.h.p.
- **Fast Evaluation of $ a_n $**:
  - Direct recurrence: $ O(nmd) $.
  - Optimized: Avoid division by $ P_0(i) $ by maintaining scaled values $ u_i = a_i \prod_{t=m}^{i-1} P_0(t) $. Then use matrix product $ U_n = U_0 \prod M(i) $, where $ M(i) $ encodes recurrence.
  - Compute product of polynomial matrices using point-value evaluation and doubling technique. Shift points via Lagrange interpolation in $ O(d \log d) $ per shift.
  - Total complexity: $ O(\sqrt{nd}(m^3 + m^2 \log(nd))) $ using block-wise computation and FFT-based shifts.

#### **Example Insights**
- **Tetromino Tiling**: State space DP leads to linear recurrence; Berlekamp-Massey finds compact recurrence (e.g., order 34), enabling $ O(\log n) $ query.
- **Expected Steps in Graph**: Formulate linear equations; coefficient matrix is sparse → use recurrence method to solve in $ O(n^2) $.
- **Chef Recurrence**: Functional equation $ g = Kx + Axg + Bg^2 $ implies algebraic GF → P-recursive → find recurrence and iterate.
- **Rabbit Trap Probability**: Use generating functions over two variables; diagonal extraction yields algebraic series → P-recursive. Use DP + recurrence fitting.
- **Labeled DAG Counting**: Exponential generating functions lead to algebraic $ F(x) $, so $ e^{F(x)} $ is D-finite → result is P-recursive sequence.