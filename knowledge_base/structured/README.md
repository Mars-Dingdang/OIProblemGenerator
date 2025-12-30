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

## Automated Population

This knowledge base is primarily populated automatically from `OI-wiki.pdf` using the `src/auto_populate_kb.py` script.

### Usage

```bash
# Populate specific categories
python src/auto_populate_kb.py --category data_structures,string --limit 100

# Use parallel processing with multiple API keys
python src/auto_populate_kb.py --category misc,graph_theory --limit 1000 --workers 4 --api_keys "sk-...,sk-..."
```

The script uses an LLM (e.g., DeepSeek-V3.2-Instruct or Qwen3) to extract:
1.  **Metadata**: Name, complexity, scenarios.
2.  **Template**: Standard C++ implementation.
3.  **Tricks**: Key observations and advanced techniques.

## Manual Addition

You can also manually add or edit algorithms:

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

## Rebuilding the Vector Database

After adding new files (either automatically or manually), you must rebuild the vector database so the Agent can access the new knowledge:

```bash
python src/main.py --build_kb
```
