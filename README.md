# OI Problem Generator
This repository contains an LLM agent that can automatically generate challenging OI problems, including problem statements (in LaTeX), test cases (in .in and .out files and respective data generators in c++), and solutions (in LaTeX for editorial) and std (in .cpp). 

User can specify the desired difficulty level (Codeforces rating, Atcoder level, luogu level) and problem topics and algorithms (data structures, graph, DP, or more specific topics like parametric network flow, Splay tree, Suffix automaton, etc.). The agent will then generate a complete OI problem based on the given specifications and the knowledge it has. 

The agent should be able to generate problems that are novel and not present in existing problem sets. The generated problems should be well-structured, with clear problem statements, constraints, and examples. The test cases should cover various edge cases and scenarios to ensure the robustness of the solutions. 

The agent should base its data base and learn from existing OI problems on popular OI platforms like Codeforces, Atcoder, luogu, etc, and algorithms from OIWiki (www.oikwiki.org) and papers by 国家集训队 (https://github.com/Fesdrer/NOIpaper). Also, the author gives the agent several books on competivtive programming and OI such as 《算法竞赛入门经典》, 《算法竞赛进阶指南》, *Algorithm Design*, *Introduction to Algorithms*, etc. and several self-written programs on various algorithms and data structures.

## Installation

1. Install dependencies:
   ```bash
   pip install -r requirements.txt
   ```
2. Configure environment variables:
   - Create a `.env` file in the root directory.
   - Add your API Key and Base URL:
     ```env
     OPENAI_API_KEY=your_api_key_here
     OPENAI_BASE_URL=https://llmapi.paratera.com/v1
     ```
   - Ensure you have `g++` (MinGW) installed and in your PATH for C++ code verification.

## Usage

### 1. Build Knowledge Base (First Run)
Before generating problems, you need to ingest the provided PDF books and papers into the vector database. This allows the agent to retrieve relevant algorithms and tricks.

```bash
python src/main.py --build_kb
```
*This process may take a while depending on the number of PDFs. It uses a local embedding model (`all-MiniLM-L6-v2`), so no API costs are incurred for this step.*

### 2. Generate Problems
Run the generator via command line:

```bash
# Basic usage (uses default model Qwen3-235B-A22B-Thinking-2507)
python src/main.py --difficulty "Codeforces 1500" --topic "Dynamic Programming"

# Select a specific model
python src/main.py --difficulty "Codeforces 2400" --topic "Graph Theory" --model "DeepSeek-V3.2-Thinking"

# Available models:
# - Qwen3-235B-A22B-Thinking-2507 (Default)
# - DeepSeek-V3.2-Thinking
# - DeepSeek-R1-0528

# Specify output directory
python src/main.py --difficulty "Luogu Blue" --topic "Graph Theory" --output_dir "./my_problems"
```

The generated files (statement, solution, generator, editorial) will be saved in the `problems/<problem_title_slug>/` directory.

## Knowledge Base
The `knowledge_base/` directory currently contains:
- *Algorithm Design* by Jon Kleinberg, Eva Tardos
- *Introduction to Algorithms* (CLRS)
- *OI Wiki* (PDF version)
- *NOI Papers* (National Olympiad in Informatics papers from 1999-2025)

You can add more PDF files to this directory and run `python src/main.py --build_kb` to update the knowledge base.
 