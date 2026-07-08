# CS 211 Word Ladder Generator

A C program that finds the shortest word ladder between two words using BFS (breadth-first search). A word ladder is a sequence where each step changes exactly one letter to reach a new valid word.

## How to run

Click **Run** — it will compile and launch the interactive program in the console.

When prompted:
1. Enter a word length (e.g. `4` for four-letter words)
2. Enter the dictionary filename: `words.txt` (included)
3. Enter a start word (e.g. `cat`)
4. Enter a final word (e.g. `dog`)

The program prints the shortest ladder between the two words.

## Files

| File | Description |
|------|-------------|
| `main.c` | Word ladder source code (C) |
| `words.txt` | English word dictionary (~370k words) |
| `Makefile` | Build targets: `make build`, `make run`, `make clean` |

## Build manually

```bash
make build   # compile
make run     # run
make clean   # remove binary
```

## User preferences

- Keep the original C source structure intact.
