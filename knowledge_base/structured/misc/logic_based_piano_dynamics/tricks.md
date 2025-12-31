# 计算机逻辑与艺术初探——基于逻辑的钢琴演奏音符力度模型

**Author:** 赵晟宇

### Key Ideas and Observations

- **MIDI Input/Output**: The algorithm takes MIDI files (pitch, start/end time, pedal info) and outputs per-note velocity in [1,127], preserving original timing.

- **Binding Degree for Segments**:
  - A segment’s cohesion is measured via `BindingDeg(P)` combining temporal continuity (`1 - empty_length / total_length`) and harmonic coherence.
  - Harmonic coherence uses a lookup table `H(u,v)` based on semitone intervals modulo 12, favoring consonant intervals (e.g., unison, perfect fifth).
  - Note响度 (loudness) is modeled with exponential decay: `V(u) = (1 - exp(-αs * duration)) / αs`, making shorter notes contribute less.

- **HarmonyDeg(P)**:
  - Weighted sum over all note pairs: each note's contribution is scaled by its loudness and the average harmony of its relation to others, raised to power βh (set to 3.0), amplifying strong harmonic cores.

- **AvgBindingDeg(P)**:
  - Normalizes binding degree by total loudness: `BindingDeg(P) / V(P)`, giving a density-aware cohesion metric in [0,1].

- **Compound Segment Tree (Recursive Binary Split)**:
  - Entire piece starts as one segment; recursively split at note boundaries into left/right sub-segments to maximize **composite binding degree**.
  - **ComBindingDeg(P)** combines current segment’s binding and children’s, with decay factor αc=0.5: 
    - If split: `BindingDeg(P) + αc*(BindingDeg(lP) + BindingDeg(rP))`
    - Else: `BindingDeg(P)/(1−αc)` — models infinite continuation.
  - Solved via interval DP in O(N³): for each O(N²) segment, try O(N) split points.

- **Dynamic Gain from Segment Structure**:
  - Each segment contributes linearly decreasing gain toward its edges: `gain_u|P = min((start_u − start_P)/duration_lP, (end_P − end_u)/duration_rP) * gain_P`.
  - `gain_P` depends on AvgBindingDeg(P), randomization `Rand(P)` (biased by pitch deviation σP), and distance from split point to edge to avoid abrupt changes.

- **Compound Melody Tree**:
  - After segmentation, decompose melody into binary tree of sub-melodies to maximize total melodic smoothness.
  - **Melodic smoothness** at note Qi depends on slope difference between incoming/outgoing intervals in pitch-time space, weighted by truncated loudness and smoothed via Gaussian-like kernel with γr=1/32.
  - Uses dynamic programming: state `f[Qi][ul,vl][ur,vr]` tracks last two notes in each sub-melody. Transition: add current note to left or right melody.
  - Effective state count is O(n³) due to dependency on previous notes.
  - Recursively split until no improvement.

- **Weighted Gain Aggregation**:
  - For each segment P, combine gains from all melodies Q weighted by their **AvgMelodyDeg(Q|P)** (melodic strength within P).
  - Final gain: `gain_u = Σ_P Σ_Q AvgMelodyDeg(Q|P) * gain_u|Q,P / Σ_Q AvgMelodyDeg(Q|P)`.

- **Hierarchy Compensation via PitchDeviation**:
  - To emphasize higher/more variable melodies, compute `PitchDeviation(Q|P) = γa*μ + γd*σ` (mean and std of pitch in Q over P).
  - Use **GlobalDeviation(Q|P)** = max over all ancestor segments P′⊇P to stabilize short-segment noise.
  - During synthesis, in leaf segments, reduce gain of the less prominent melody (lower GlobalDeviation) by the difference.

- **Post-processing**:
  - **Gain equalization**: shift and scale gains to target standard deviation `σ_expected`.
  - **Sigmoid mapping**: `vel_u = 127 / (1 + exp(-γo * gain'_u))`, then round to integer.

- **Design Philosophy**:
  - Avoids machine learning; builds on human-understandable musical logic.
  - Hierarchical, recursive structure mimics cognitive parsing of music.
  - Parameters (αs, βh, γr, αc, γa, γd, γo) are empirically tuned but interpretable.

- **Limitations & Extensions**:
  - No explicit tempo modeling, though suggested as future work.
  - Could integrate score markings (crescendo, accents) if available.
  - Approximate algorithms feasible for large N due to heuristic nature.