# ⚙️ Algorithms

This folder contains a curated set of classic and widely-used **algorithms**, implemented with clarity, performance, and educational value in mind.

These algorithms are designed to be standalone, language-agnostic in concept, and reusable across multiple domains such as strings, combinatorics, and number theory.

---

## 📁 Folder Structure & Descriptions

### ✅ [`kmp.c`](./kmp.c) – Knuth-Morris-Pratt String Search
- **Complexity:** `O(n + m)` where `n = text length`, `m = pattern length`
- **Description:** Efficiently searches for a substring inside a text. Uses a prefix table (`lps[]`) to skip unnecessary comparisons.
- **Use Cases:** Text editors, search engines, bioinformatics, log analysis.
- 📖 [Wikipedia - KMP Algorithm](https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm)

---

### ✅ [`pow.c`](./pow.c) – Fast Exponentiation (Square-and-Multiply)
- **Complexity:** `O(log e)`
- **Description:** Computes `base^exp` efficiently using the binary representation of the exponent.
- **Use Cases:** Modular arithmetic, cryptographic algorithms (e.g., RSA), number theory.
- 📖 [Binary Exponentiation on CP-Algorithms](https://cp-algorithms.com/algebra/binary-exp.html)

---

### ✅ [`permutations.c`](./permutations.c) – Heap's Algorithm for Permutations
- **Complexity:** `O(n!)` – all permutations of `n` elements
- **Description:** Generates permutations with minimal swaps using a recursive or iterative approach.
- **Use Cases:** Combinatorics, backtracking, testing all configurations, puzzle solvers.
- 📖 [Heap's Algorithm - Wikipedia](https://en.wikipedia.org/wiki/Heap%27s_algorithm)

---

### ✅ [`edit_distance.c`](./edit_distance.c) – Levenshtein Edit Distance
- **Complexity:** `O(n * m)` where `n = length of string A`, `m = length of string B`
- **Description:** Calculates the minimum number of edits (insertions, deletions, substitutions) required to transform one string into another.
- **Use Cases:** Spell checkers, approximate string matching, DNA sequence alignment, NLP.
- 📖 [Levenshtein Distance - Wikipedia](https://en.wikipedia.org/wiki/Levenshtein_distance)

---

## 🧠 Why This Folder Exists

Many algorithms transcend specific data structures. This folder captures those that:

- Are **fundamental** to computer science and algorithmic thinking
- Solve general-purpose problems not tied to trees, graphs, etc.
- Are **reusable utilities** in competitive programming, system design, and real-world applications

---

## 🚀 Running the Examples

Each `.c` file is self-contained and can be compiled using any standard C compiler.
