# C Data Structures — CodeChum-Style Practice Exam

A 12-problem practice exam in C covering four data-structures topics. Each topic is a
separate folder with its own problem statements, starter files, answer key, test cases,
and auto-grader.

> **Terminology note:** this exam uses *open hashing* for separate chaining (data lives
> outside the table) and *closed hashing* for open addressing (all data lives inside the
> table), which is the convention used by most introductory data-structures courses.

| # | Folder | Topic | Problems | Points |
|---|--------|-------|----------|--------|
| 1 | [Open Hashing](Open%20Hashing/) | Separate chaining | 3 | 100 |
| 2 | [Closed Hashing](Closed%20Hashing/) | Open addressing (linear, quadratic, double hashing) | 3 | 100 |
| 3 | [Bit Vectors](Bit%20Vectors/) | Bitsets, bitwise operations, sieve | 3 | 100 |
| 4 | [Priority Queue](Priority%20Queue/) | Binary heaps, custom comparators, k-way merge | 3 | 100 |

**Total:** 400 points · **Suggested time:** 60 minutes per topic

## Problem overview

| Topic | P1 (30 pts) | P2 (35 pts) | P3 (35 pts) |
|-------|-------------|-------------|-------------|
| Open Hashing | Bucket Brigade | Lost and Found | Word Watch |
| Closed Hashing | Linear Probing Lot | Quadratic Quest | Double Trouble |
| Bit Vectors | Bit Vector Playground | Sieve of Bits | Bitset Algebra |
| Priority Queue | Min-Heap Machine | ER Triage | Merge the Streams |

Every problem includes:

- a full CodeChum-style statement (`problems/Pn.md`),
- a starter file with function skeletons and TODOs (`starter/Pn.c`),
- a working answer key (`solutions/Pn.c`),
- four test cases (`tests/Pn/01.in` … `04.in` with matching `.out` files).

## Quick start

```powershell
# Enter a topic folder
cd "Open Hashing"

# Read the problems (UTF-8)
Get-Content -Encoding UTF8 .\problems\P1.md

# Write your solution in the starter file, then grade it
.\run_tests.ps1 -Problem P1 -Source .\starter\P1.c

# Grade the included answer key
.\run_tests.ps1

# Grade all four topics at once (from this top-level folder)
.\run_all.ps1
```

If PowerShell blocks the scripts, run them with:

```powershell
powershell -ExecutionPolicy Bypass -File .\run_tests.ps1 -Problem P1 -Source .\starter\P1.c
```

## Requirements

- **GCC** on `PATH` (the scripts use `gcc -std=c11`). MinGW-w64 or MSYS2 works on Windows.
- **Windows PowerShell 5.1** or PowerShell 7+.

## How the grader works

1. Compiles the chosen source with `gcc -std=c11 -O2 -Wall -Wextra`.
2. Runs it once per `.in` file with that file as standard input.
3. Compares standard output with the matching `.out` file, ignoring trailing spaces on
   each line and trailing blank lines.
4. Enforces a 5-second per-test timeout.
5. Exits with code `0` only if every test passes.

## Folder layout

```
C Coding Practice/
├── README.md                 <- this file
├── run_all.ps1               <- grade every topic
├── Open Hashing/
│   ├── README.md             <- exam mechanics for this topic
│   ├── problems/             <- P1.md, P2.md, P3.md
│   ├── starter/              <- P1.c, P2.c, P3.c
│   ├── solutions/            <- answer key
│   ├── tests/P1..P3/         <- 01.in/.out ... 04.in/.out
│   └── run_tests.ps1
├── Closed Hashing/           <- same layout
├── Bit Vectors/              <- same layout
└── Priority Queue/           <- same layout
```

## Notes for instructors

- The answer key passes all 48 tests. Run `.\run_all.ps1` to confirm the environment.
- Suggested partial credit: `problem points × (tests passed / 4)`, rounded to the nearest
  whole point.
- The tests include edge cases such as empty tables, negative keys, duplicates, full
  tables, leading zeros, a 64-bit vector, and priority ties.
- Students can read the `.in` and `.out` files, so use the included hidden-style cases as
  practice only. For a real exam, replace them with fresh cases and remove `solutions/`.
