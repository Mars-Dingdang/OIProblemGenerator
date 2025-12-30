
PROBLEM_SETTING_GUIDELINES = """
**OI Problem Setting Guidelines (Based on OI Wiki & Standard Practices)**

1.  **Problem Statement**:
    *   **Clarity**: The problem description must be unambiguous. Avoid vague terms.
    *   **Story**: A background story is encouraged but must be clearly separable from the formal task.
    *   **Formal Definition**: Clearly define the input objects (e.g., "A directed acyclic graph with $N$ vertices...").

2.  **Input/Output Format**:
    *   Specify the exact format (e.g., "The first line contains an integer $T$...").
    *   Specify ranges and types (e.g., "integers", "lowercase English letters").

3.  **Constraints**:
    *   Provide constraints for ALL variables ($N, M, Q, A_i$, etc.).
    *   Specify time limit (usually 1.0s - 2.0s) and memory limit (256MB - 512MB).
    *   Ensure the constraints distinguish between intended efficient solutions and brute-force/suboptimal solutions.

4.  **Difficulty & Solvability**:
    *   The problem must be solvable within the time limit using the intended algorithm.
    *   Avoid problems that rely solely on heavy implementation without algorithmic insight (unless intended).
    *   **Thinking Level**: For high-difficulty problems (NOI/Codeforces 2400+), the solution should require at least one non-trivial transformation or observation.

5.  **Test Cases**:
    *   Include edge cases (min/max constraints, empty structures, etc.).
    *   **Sample**: Provide at least one non-trivial sample case with explanation.
"""

IDEATION_PROMPT_TEMPLATE = """
You are an expert competitive programming problem setter (Codeforces Grandmaster / NOI Level).
Your goal is to design a high-quality, novel algorithmic problem.

**Guidelines**:
{guidelines}

**Target**:
*   **Difficulty**: {difficulty}
*   **Topic**: {topic}

**Knowledge Context**:
{context}

**Task**:
1.  Analyze the provided Knowledge Context (especially Level 3 Tricks/Observations).
2.  Brainstorm a core algorithmic idea that combines the Topic with a specific Trick or Observation.
3.  Wrap this core idea in a problem setting.
4.  Ensure the difficulty matches the target by adjusting constraints or adding layers of complexity.

**Output Format**:
Return a JSON object with the following fields:
*   `title`: Problem title.
*   `description`: High-level problem description.
*   `input_format`: Draft of input format.
*   `output_format`: Draft of output format.
*   `constraints`: Key constraints (N, M, values).
*   `algorithm`: The core algorithm(s) used.
*   `complexity`: Time and space complexity.
*   `key_insight`: The "Aha!" moment or key observation required to solve it.
"""
