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

## Updates

### 2025-12-30: Knowledge Base Refactoring & Model Optimization
- **Structured Knowledge Base**: Refactored the knowledge base to support a 3-level structured format (Metadata, Template, Tricks) for better retrieval accuracy.
- **Auto-Population Script**: Added `src/auto_populate_kb.py` to automatically extract structured algorithm data from the OI Wiki PDF using LLMs (defaulting to `DeepSeek-V3.2-Instruct`, later I used `Qwen3-235B-A22B-Instruct-2507` due to connection problems of DeepSeek, and I found the latter much faster than DeepSeek though DeepSeek indeed gave more detailed summary in the json file).
- **Prompt Engineering**: Integrated `PROBLEM_SETTING_GUIDELINES` into the default prompts to ensure generated problems meet high-quality OI standards.
- **Model Selection**: Added support for multiple models (Qwen3, DeepSeek-V3.2, DeepSeek-R1) via the `--model` argument.
- **Enhanced Retrieval**: Updated `src/knowledge_base.py` to prioritize structured knowledge retrieval before falling back to vector search.

### 2025-12-31: NOI Papers Activation & Knowledge Base Expansion
- **NOI Papers Integration**: Successfully processed National Olympiad in Informatics (NOI) papers from 2013 to 2025.
- **Automated Extraction**: Implemented `src/activate_noi_papers.py` to automatically extract paper metadata, summaries, complexity analysis, and advanced tricks/observations from the PDF collections.
- **Smart Parsing**: Improved PDF parsing logic to accurately handle Table of Contents extraction and fuzzy page matching for locating specific papers within large PDF volumes.
- **Model Usage**: Utilized `Qwen-235B-A22B-Instruct-2507` for high-quality text analysis and structured data extraction from the papers.
- **Knowledge Base Rebuild**: Rebuilt the vector and structured knowledge base to include these high-value resources, significantly enhancing the agent's ability to reference advanced competitive programming techniques.
 