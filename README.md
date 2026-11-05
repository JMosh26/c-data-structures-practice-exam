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
| Open Hashing | Locker Loop | Reunion Registry | Tag Tournament |
| Closed Hashing | Parking Lot | Vault Codes | Ghost Gallery |
| Bit Vectors | Light Panel | Prime Stamp | Set Duel |
| Priority Queue | Roller Coaster | Air Traffic | Stream Merger |

### Twists at a glance

| Problem | What makes it different |
|---------|-------------------------|
| Locker Loop | New keys go at the **head** of each chain, then chain statistics are printed. |
| Reunion Registry | Weighted **string** hash with deletion and 1-based chain positions. |
| Tag Tournament | **Case-insensitive** tags, counts, and a top-K ranking with a lexicographic tie-break. |
| Parking Lot | Linear probing that reports a status for **every** arrival plus a probe total. |
| Vault Codes | Quadratic probing that prints the **entire probe path** for each insertion. |
| Ghost Gallery | Double hashing with **tombstones** and tombstone reuse. |
| Light Panel | 32-bit **range** SET / CLEAR / FLIP operations instead of single bits. |
| Prime Stamp | A bit-vector sieve that also reports the **largest prime gap** and its pair. |
| Set Duel | Set algebra with **subset**, **disjoint**, and **same** comparisons. |
| Roller Coaster | A min-heap with batch **`TAKE k`** extraction and an internal-array dump. |
| Air Traffic | A **three-key** comparator: emergency, then time, then flight name. |
| Stream Merger | A **descending stable** k-way merge across non-increasing streams. |

Every problem includes:

- a full CodeChum-style statement (`problems/Pn.md`),
- a starter file with function skeletons and TODOs (`starter/Pn.c`),
- a working answer key (`solutions/Pn.c`),
- four test cases (`tests/Pn/01.in` … `04.in` with matching `.out` files).

## Repository setup

These steps assume Git is installed. If you already have a local copy of the project,
skip to [Quick start](#quick-start).

### Clone the repository

```powershell
git clone https://github.com/YOUR-USERNAME/c-data-structures-practice-exam.git
cd "c-data-structures-practice-exam"
```

If you downloaded the project as a ZIP instead, extract it and open PowerShell in the
extracted folder.

### Publish this folder as a new GitHub repository

1. Create a new **empty** repository at <https://github.com/new>.
   - Do **not** initialize it with a README, `.gitignore`, or license. This project
     already contains those files.
2. Connect the local repository to GitHub and push:

```powershell
git remote add origin https://github.com/YOUR-USERNAME/REPO-NAME.git
git push -u origin main
```

Replace `YOUR-USERNAME` and `REPO-NAME` with your GitHub username and repository name.

If `origin` already exists, update it instead:

```powershell
git remote set-url origin https://github.com/YOUR-USERNAME/REPO-NAME.git
git push -u origin main
```

If GitHub rejects the push because the remote repository already has commits, rebase
onto it and try again:

```powershell
git pull --rebase origin main
git push -u origin main
```

### Authentication

On the first HTTPS push, Git Credential Manager should open a browser sign-in window.
If Git asks for a password, use a **Personal Access Token** (PAT), not your GitHub
account password.

If you use SSH keys, use the SSH remote instead:

```powershell
git remote add origin git@github.com:YOUR-USERNAME/REPO-NAME.git
git push -u origin main
```

### Save later changes

After editing the project, commit and push normally:

```powershell
git add .
git commit -m "Describe your change"
git push
```

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
  tables, quadratic-probe failure cycles, tombstones, 64-bit sets, a 1,000,000 sieve,
  comparator ties, and empty streams.
- Students can read the `.in` and `.out` files, so use the included hidden-style cases as
  practice only. For a real exam, replace them with fresh cases and remove `solutions/`.
