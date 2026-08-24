# Competitive programming

Solved problems from Codeforces, LeetCode and HackerRank, mostly in C++. Each
folder holds the solution and a screenshot of the statement, so it reads without
the original site and survives a problem going offline.

A practice log, not a library.

<!-- BEGIN GENERATED: STATS -->
![Problems](https://img.shields.io/badge/problems-395-555) ![CodeForces](https://img.shields.io/badge/CodeForces-238-1f8acb) ![HackerRank](https://img.shields.io/badge/HackerRank-77-2ec866) ![LeetCode](https://img.shields.io/badge/LeetCode-80-ffa116)

| Platform | Solved | Index |
|:---------|-------:|:------|
| CodeForces | 238 | [browse](CodeForces/README.md) |
| HackerRank | 77 | [browse](HackerRank/README.md) |
| LeetCode | 80 | [browse](LeetCode/README.md) |
| **Total** | **395** | |

Languages: C++ (392), C (5), SQL (2), Bash (1)

Span: 2025-07-11 to 2026-08-24. 12,077 lines of solution code.

```
Problems solved per month

2025-07  ######################################## 162
2025-08  ############## 55
2025-09  ###### 23
2025-10  ####### 30
2025-11  ######## 31
2025-12  ######## 31
2026-01  ######## 31
2026-02  ###### 26
2026-03  # 3
2026-04   0
2026-05   0
2026-06   0
2026-07   0
2026-08  # 3
```
<!-- END GENERATED: STATS -->

## Templates

[`templates/`](templates/README.md) has a starting file per platform, plus a
Codeforces toolkit with DSU, Fenwick, segment tree, sparse table, sieve, modular
arithmetic, Z-function and Dijkstra. It also separates the speed tricks that work
from the ones that are folklore.

## Layout

```
<Platform>/problems/<Problem title>/
    code.cpp      the solution
    image.png     screenshot of the statement
```

CodeForces uses `forces.cpp`, not `code.cpp`, from when this held only
Codeforces problems. Renaming 230 files would bury the per-problem dates the
index reads out of git.

Some problems keep two solutions (`forcesv1.cpp`, `forcesv2.cpp`,
`forces-optimized.cpp`) where the first attempt passed but was worth rewriting.
Two keep a second statement page as `image-2.png`.

## Running a solution

```
g++ -std=c++17 -O2 -o solution "CodeForces/problems/Bit++/forces.cpp"
./solution < input.txt
```

LeetCode solutions are `Solution` class bodies built against the site's harness
and do not compile standalone. Three are SQL or Bash.

## Why the tree is flat

Filing 393 folders under `graphs/`, `dp/` and so on means renaming paths every
time a problem fits somewhere else, and every rename breaks the links.
`tools/build_index.py` derives the tables instead, from the directory listing and
from git history for the solve dates. Adding a problem stays a single commit.

```
python tools/build_index.py           rewrite the generated files
python tools/build_index.py --check   fail if they are stale
python tools/check_repo.py            verify the layout
```

`check_repo.py` exists because this drifted once: empty folders, filenames left
behind by a copy, and a Cyrillic lookalike pasted in from a problem title that
made it unsearchable. Both run in CI, alongside a compile sweep of every
standalone solution.

## Attribution

Statement screenshots belong to Codeforces, HackerRank and LeetCode, and are
stored for reference.
