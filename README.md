# 📚 USM Competitive Programming Handbook

A comprehensive collection of algorithms and data structures for competitive programming, maintained by Universidad Técnica Federico Santa María (USM) students.

## 🚀 Quick Start

### Prerequisites
- [Typst](https://typst.app/) - A modern markup-based typesetting system

### Compilation
```bash
typst compile main.typ
```

This generates a PDF handbook with all algorithms organized by category.

## 📖 Contents

The handbook includes implementations for:

- **🔧 General** - Templates and troubleshooting guides
- **🔤 Strings** - String processing algorithms (KMP, Z-algorithm, Suffix Array, Trie, etc.)
- **⚡ Algorithms** - General algorithms (Mo's algorithm, Tortoise-Hare cycle detection)
- **📊 Data Structures** - Advanced data structures (Segment Trees, Fenwick Trees, Treaps, etc.)
- **🧮 Mathematics** - Number theory, linear algebra, and polynomial operations
- **📈 Graphs** - Graph algorithms (DFS, BFS, Shortest paths, Network flows, etc.)
- **📐 Geometry** - Computational geometry (Convex Hull, Point operations, etc.)
- **🎯 Dynamic Programming** - DP optimizations and classic problems
- **🔀 Combinatorics** - Advanced combinatorial algorithms

## 📝 Contributing Guidelines

### Code Style
- **Naming**: Use lowercase with hyphens for folders and files (`knuth-morris-pratt` → `kmp`)
- **File Extensions**: Only `.cpp` and `.typ` files allowed
- **Indentation**: Use exactly **2 spaces** (no tabs)
- **Length**: Keep filenames under 18 characters when possible
- **Atomicity**: Each file should contain only one algorithm/data structure

### Code Requirements
- **Documentation**: Every C++ file must start with a multi-line comment describing the algorithm
- **No Macros**: Avoid competitive programming macros like `rep`, `repx`, etc.
- **Clean Code**: Write readable, well-structured code

### File Structure
```
content/
├── algorithms/            # General algorithms
├── combinatorial/         # Combinatorial algorithms
├── data-structures/       # Advanced data structures
├── dynamic-programming/   # DP techniques
├── general/               # Templates and utilities
├── geometry/              # Computational geometry
├── graphs/                # Graph algorithms
├── maths/                 # Mathematical algorithms
└── strings/               # String algorithms
```

## 🎯 Project Goals

1. **Concise Implementations** - Provide short, efficient algorithm implementations
2. **Educational Value** - Include clear descriptions and explanations
3. **Competitive Ready** - Code optimized for programming contests
4. **Comprehensive Coverage** - Cover all essential competitive programming topics

## 🚧 Roadmap

- [ ] Additional dynamic programming techniques
- [ ] Karatsuba polynomial multiplication
- [ ] Advanced polynomial operations

## 👥 Team

**Maintainers:**
- Gabriel Carmona (MrYhatoh)
- Carlos Lagos (CharlesLakes) 
- Sebastián Torrealba (storrealbac)
- Abner Vidal (abner_vidal)

**Contributors:**
- Javier Oliva (JOliva)
- Marcelo Lemus (MarceloL)

## 📄 License

This project is licensed under the terms specified in the [LICENSE](LICENSE) file.

---

*Built with ❤️ for the competitive programming community at USM*
