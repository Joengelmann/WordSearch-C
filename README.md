# Word Search Puzzle Solver (C++)

A **Word Search Puzzle Solver** implemented in **C++**.  
The program takes in a **dictionary of words** (`words.txt`) and a **puzzle file** (`puzzle.txt`), then searches the puzzle grid for all dictionary words.  

Tested on a `250 x 250` puzzle — solved in under **30 seconds** on a standard computer.

---

## Features

- Supports **large word search puzzles** (250x250+).
- Efficient search using **unordered_set** dictionary lookups.
- Searches in **all 8 directions** (horizontal, vertical, diagonal).
- Reports words found along with their **start and end coordinates**.
- Minimum word length: **6 letters** (can be adjusted in code).

---

## Example Output

```
Word was found!: teacher from [23,17] to [23,23]
Word was found!: science from [100,15] to [106,15]
Word was found!: project from [199,10] to [193,16]
...
```

---

## File Requirements

- **puzzle.txt** → word search grid (space-separated letters per line, equal width each row).
- **words.txt** → dictionary file (one word per line).

Example `puzzle.txt` (tiny 5x5 sample):

```
t e a c h
s c i e n
p r o j e
l a n g u
c o d e r
```

Example `words.txt`:

```
teacher
science
project
language
coder
```

---

## Build & Run

Requires a **C++11-compatible compiler** (e.g., `g++`, Clang).

```bash
g++ -std=c++11 -O2 -o wordsearch wordsearch.cpp
./wordsearch
```

---

## Performance

- Tested with **250x250 puzzle** and large dictionary
- Runtime: **<30 seconds**
- Optimized using:
  - `unordered_set` dictionary for O(1) lookups
  - Directional scanning with bounds checking
  - Early stopping on invalid directions

---

## Code Overview

- **`struct found_word`**: stores word, start, and end coordinates
- **`class puzzle`**: handles puzzle and dictionary loading, solving algorithm
- **`solve()`**:
  - Iterates across all cells
  - Expands in 8 directions
  - Checks dictionary membership for substrings (>= 6 letters)
  - Collects all valid words
- **`main()`**: constructs puzzle, runs solver, prints results
