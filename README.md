# Word Ladder Generator

A C program that finds the **shortest word ladder** between two words using breadth-first search (BFS). A word ladder is a sequence of words where each step changes exactly one letter, and every intermediate word is valid.

**Example:** `cat` → `bat` → `bad` → `bad` → `bed` → `red` → `rod` → `dog`

---

## How It Works

1. You choose a word length (e.g. 4 for four-letter words)
2. The program filters the dictionary to only words of that length
3. You enter a start word and a final word
4. BFS explores all single-letter neighbors of each word until it reaches the target, guaranteeing the shortest possible ladder

---

## Getting Started

### Run on Replit

Click **Run** — the program compiles and launches automatically in the console.

### Build Locally

```bash
# Requires GCC
make build   # compile → produces ./wordladder
make run     # compile + run
make clean   # remove compiled binary
```

---

## Usage

```
Welcome to the CS 211 Word Ladder Generator!

Enter the word size for the ladder: 4

Setting the start 4-letter word...
  Enter a 4-letter word: cold

Setting the final 4-letter word...
  Enter a 4-letter word: warm

Shortest Word Ladder found!
    warm
    worm
    word
    cord
    core
    care
    dare
    date
    ...
Word Ladder height = 8
```

If no ladder exists between the two words, the program will say so.

If you enter an invalid word 5 times in a row, the program picks a random word for you.

---

## Project Structure

```
├── main.c        # Word ladder source code (C)
├── words.txt     # English dictionary (~370,000 words)
├── Makefile      # Build targets: build, run, clean
└── README.md
```

---

## Key Functions

| Function | Description |
|---|---|
| `countWordsOfLength` | Counts words of a given length in the dictionary |
| `buildWordArray` | Loads matching words into a sorted array |
| `findWord` | Binary search over the word array |
| `findShortestWordLadder` | BFS to find the shortest ladder |
| `insertWordAtFront` | Prepends a word to a ladder (linked list) |
| `copyLadder` | Deep-copies a ladder for BFS branching |
| `freeLadder` / `freeWords` | Memory cleanup |

---

## Data Structures

- **`WordNode`** — singly linked list node holding one word; chained together to form a ladder
- **`LadderNode`** — singly linked list node holding a `WordNode*` (ladder); used as the BFS queue

---

## Requirements

- GCC with C11 support (`-std=c11`)
- `words.txt` dictionary in the same directory as the binary

---

*CS 211 — Programming Practicum, University of Illinois Chicago, 2024*
