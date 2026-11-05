# Closed Hashing — Practice Exam

**Topic:** Closed hashing / open addressing
**Problems:** 3
**Total points:** 100
**Suggested time:** 60 minutes

## Exam mechanics

- Write each solution in C (C11).
- Read from **standard input** and write to **standard output**.
- Do not print prompts, labels, or extra blank lines unless the statement asks for them.
- Output must match exactly. The grader ignores trailing spaces at the end of a line and trailing blank lines.
- The standard C library is allowed. Third-party libraries are not.
- Each problem is independent.

## Problem set

| # | Title | Difficulty | Points | Statement |
|---|-------|------------|--------|-----------|
| P1 | Linear Probing Lot | Easy | 30 | [problems/P1.md](problems/P1.md) |
| P2 | Quadratic Quest | Medium | 35 | [problems/P2.md](problems/P2.md) |
| P3 | Double Trouble | Medium | 35 | [problems/P3.md](problems/P3.md) |

## Folder guide

| Folder | Contents |
|--------|----------|
| `problems/` | Full problem statements |
| `starter/` | Function skeletons with TODOs and a suggested plan |
| `solutions/` | Answer key — try the problems before opening this |
| `tests/` | Input/output test cases used by the grader |
| `run_tests.ps1` | Compiles a source file and runs it against the tests |

## Compile and run manually

```powershell
cd "Closed Hashing"
gcc -std=c11 -O2 -Wall -Wextra -o P1 .\starter\P1.c
Get-Content .\tests\P1\01.in | .\P1.exe
```

## Auto-grade your attempt

```powershell
# Grade one problem
.\run_tests.ps1 -Problem P1 -Source .\starter\P1.c

# Grade every problem in this folder
.\run_tests.ps1
```

`run_tests.ps1` with no arguments grades the files in `solutions/`. Use `-Problem` and
`-Source` to grade your own file. The script exits with code `0` only when every test passes.

## Scoring suggestion

For each problem, award:

```
points earned = problem points × (tests passed / total tests)
```

rounded to the nearest whole point.
