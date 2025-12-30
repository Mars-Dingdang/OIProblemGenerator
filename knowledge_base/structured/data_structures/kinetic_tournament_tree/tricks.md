- **Certificate Maintenance**: Each internal node maintains a certificate (`swc`) representing when its two children's values will cross (i.e., their linear functions intersect). This allows proactive updates when the maximum source changes.

- **Lazy Propagation with Time Shift**: The lazy tag represents a left shift $ \delta $ in the function argument ($ f(x) \leftarrow f(x+\delta) $). Crucially, this shifts both the current value at 0 and the certificate failure time by $ -\delta $.

- **Event-Driven Update via `checkswitch`**: After applying a lazy update, we recursively check if any certificate has failed (i.e., `swc <= 0`). If so, we descend and recompute using `push_up`, which may trigger further switches.

- **Potential Method for Complexity Analysis**: The amortized analysis uses potential $ \Phi = \sum \alpha(x) $, where $ \alpha(x) $ depends on depth and whether the lower-slope function is currently larger. This yields $ O(\log n) $ amortized per event and overall $ O(n \log^2 n + m \log^3 n) $.

- **Generalization to Higher-Order Functions**: For functions with at most $ s $ intersections, use $ \alpha(x) = d(x) \log_{s+1} I(x) $, enabling extension to polynomials.

- **Implicit Event Queue**: Instead of storing events globally, each node tracks its own next failure time, making it efficient and localized.

- **IntegerPart Trick**: Use `ceil((b1 - b2)/(k2 - k1))` to compute first positive crossing time, avoiding floating-point precision issues by rounding up.