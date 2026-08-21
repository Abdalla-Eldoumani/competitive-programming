# Competitive programming

Solutions to problems from Codeforces, LeetCode and HackerRank, written mostly in
C++. Every problem folder holds the code and a screenshot of the statement it
answers, so a solution can be read without opening the original site and without
depending on a problem staying online.

This is a practice log, not a library. Nothing here is meant to be imported into
another project.

<!-- BEGIN GENERATED: STATS -->
![Problems](https://img.shields.io/badge/problems-393-555) ![CodeForces](https://img.shields.io/badge/CodeForces-238-1f8acb) ![HackerRank](https://img.shields.io/badge/HackerRank-77-2ec866) ![LeetCode](https://img.shields.io/badge/LeetCode-78-ffa116)

| Platform | Solved | Index |
|:---------|-------:|:------|
| CodeForces | 238 | [browse](CodeForces/README.md) |
| HackerRank | 77 | [browse](HackerRank/README.md) |
| LeetCode | 78 | [browse](LeetCode/README.md) |
| **Total** | **393** | |

Languages: C++ (390), C (5), SQL (2), Bash (1)

Span: 2025-07-11 to 2026-08-21. 11,982 lines of solution code.

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
2026-08  # 1
```
<!-- END GENERATED: STATS -->

## Layout

```
<Platform>/problems/<Problem title>/
    code.cpp      the solution
    image.png     screenshot of the problem statement
```

CodeForces solutions are named `forces.cpp` rather than `code.cpp`. That is a
leftover from when this repository only held Codeforces problems, and renaming
230 files would bury the history of when each one was actually solved.

A few problems keep more than one solution, named `forcesv1.cpp`, `forcesv2.cpp`
or `forces-optimized.cpp`. Those are the ones where a first attempt passed but
was worth rewriting, and both versions are kept on purpose. Two problems keep a
second statement page as `image-2.png`.

## Running a solution

Codeforces and HackerRank solutions read stdin and write stdout, so they compile
and run on their own:

```
g++ -std=c++17 -O2 -o solution "CodeForces/problems/Bit++/forces.cpp"
./solution < input.txt
```

LeetCode solutions are `Solution` class bodies compiled against the site's own
harness, so they do not build standalone. Three of them are SQL or Bash instead
of C++.

## Why the folders are not sorted by topic

Filing 393 folders under `graphs/`, `dp/`, `greedy/` and so on means renaming
paths every time a problem turns out to fit somewhere else, and every rename
breaks whatever linked to it. The tree stays flat and `tools/build_index.py`
derives the tables instead, reading the directory listing for the problem set and
git history for the date each one was first solved. Adding a problem is still
just committing a folder.

```
python tools/build_index.py           rewrite the generated files
python tools/build_index.py --check   fail if they are stale
python tools/check_repo.py            verify the layout
```

`check_repo.py` is there because this drifted once already. It catches empty
folders, solutions that went missing, filenames left behind by a copy, and
Cyrillic lookalike characters pasted in from a problem title, which quietly make
a problem impossible to find by search. Both scripts run in CI on every push.

## License

The solutions are MIT licensed. The statement screenshots belong to the
platforms they came from and are included for reference only.
