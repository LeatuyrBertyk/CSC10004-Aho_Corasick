# VIETNAMESE TEXT PREPROCESSING SYSTEM WITH TRIE AND AHO-CORASICK ALGORITHM
A high-performance text preprocessing system using the Aho-Corasick Automaton for multi-pattern string matching. This project explores the evolution of search algorithms, from naive to advanced automaton-based structures, designed for processing datasets by masking junk keywords.

[![Language: C++](https://img.shields.io/badge/Language-C++-blue.svg)](https://isocpp.org/)
[![Platform: Linux](https://img.shields.io/badge/Platform-Ubuntu-orange.svg)](https://ubuntu.com/)

## Overview
This system is engineered to perform efficient multi-pattern searching on massive text. It provides a benchmark to compare four approaches: Naive Search, Standard Trie, Trie with Maximal Munch (Greedy), and Aho-Corasick.

## Repository Structure
```plaintext
Solution/
├── main.cpp
├── trie_node.h
├── global_variables.h
├── Benchmark/
│   ├── benchmark.cpp
│   └── benchmark.h
├── CoreStructure/
│   ├── Build/                  # Build Trie and fail_links
│   ├── SortAlgorithm/          # Quick sort for matches
│   └── TrieMemoryManagement/   # Manage Trie data stucture
└── SearchEngines/              # 4 main search strategies
Report.pdf
README.md
```

## Requirements
To compile and run this project, the following environment is recommended:
- **Compiler**: A `C++11` (later) compiler (e.g., `g++` or `clang++`).
- **OS**: Linux-based Ubuntu 22.04+ (recommended), Windows (10+), MacOS. 
- **Data files**: `noise_sick_50k.txt` - dictionary of 50,000 noise patterns, and `clean_corpus.txt` - large input text corpus (millions of words).
- **Storage**: SSD recommended for optimal performance.

## Getting Started
1. Clone the repository:
   ```bash
   git clone https://github.com/LeatuyrBertyk/CSC10004-Aho_Corasick
   ```
2. Compile the engine:
   ```bash
   g++ -O3 main.cpp Benchmark/*.cpp CoreStructure/*/*.cpp SearchEngines/*.cpp -o engine.exe
   ```
3. Execution:
   ```bash
   ./engine.exe
   ```

## Benchmarking & Analysis
After execution, the system outputs the Mean Execution Time (ns) across 100 random runs for two scenarios:
- Scenario 1: Fixed Dictionary $K=10,000$, increasing text length $N$.
- Scenario 2: Fixed Text $N=1,000,000$, increasing Dictionary size $K$.

The project requires a deep analysis of:
- The Backtracking Bottleneck
- Dictionary Scalability Impact
- Algorithm Strategy - Maximal Munch vs. All-Matches

## Conclusion
This implementation validates that the Aho-Corasick Automaton is the optimal solution for multi-pattern search problems in text preprocessing. Detailed empirical results and theoretical analyses can be found in `Report.pdf`.
