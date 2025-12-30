# Structured Knowledge Base

This directory contains structured knowledge for the OI Problem Generator.
The goal is to provide high-quality, curated information to the Agent, supplementing the raw PDF documents.

## Structure

The knowledge base is organized by algorithm category:

```
structured/
  ├── data_structures/
  │   ├── segment_tree/
  │   │   ├── metadata.json   (Level 1: Basic Info)
  │   │   ├── template.cpp    (Level 2: Code Template)
  │   │   └── tricks.md       (Level 3: Advanced Tricks)
  │   └── ...
  ├── graph_theory/
  │   └── ...
  └── string/
      └── ...
```

## How to Add a New Algorithm

1.  **Create a Folder**: Create a folder for the algorithm under the appropriate category (e.g., `structured/graph_theory/tarjan`).
2.  **Add `metadata.json`**:
    ```json
    {
        "name": "Algorithm Name",
        "category": "Category",
        "complexity": {
            "time": "O(N)",
            "space": "O(N)"
        },
        "scenarios": ["Scenario 1", "Scenario 2"],
        "extensions": ["Extension 1"]
    }
    ```
3.  **Add `template.cpp`**: A clean, well-commented C++ implementation.
4.  **Add `tricks.md`**: A Markdown file describing key observations, common transformations, and tricks used in high-level problems.

## Rebuilding

After adding new files, run:
```bash
python src/main.py --build_kb
```
