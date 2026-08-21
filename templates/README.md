# Templates

| File | Use for |
|:-----|:--------|
| [`codeforces.cpp`](codeforces.cpp) | Every Codeforces problem. Fast I/O, aliases, multi-test loop, debug macro. |
| [`codeforces-fast.cpp`](codeforces-fast.cpp) | A measured TLE, or any problem needing a real data structure. |
| [`hackerrank.cpp`](hackerrank.cpp) | HackerRank, which hands you a function signature rather than stdin. |
| [`leetcode.cpp`](leetcode.cpp) | LeetCode, which links a class against its own driver. |

Copy the file into the problem, delete the sections you do not need. The
toolkit is written so that deleting a block never breaks the ones above it.

## What actually matters

1. `ios_base::sync_with_stdio(false); cin.tie(nullptr);` fixes most timeouts on
   Codeforces and HackerRank. The only rule after it is not to mix `cin` with
   `scanf`.
2. Never `endl` in a loop. It flushes; `'\n'` does not.
3. If it still times out, the complexity is wrong. Nothing below fixes that.

Everything past this point is a smaller effect than any of those three.

## In the toolkit

| Structure | Cost | For |
|:----------|:-----|:----|
| `DSU` | ~O(1) amortised | connectivity, Kruskal, grouping |
| `Fenwick` | O(log n) | point add, prefix or range sum |
| `SegTree` | O(log n) | point assign, range query on any associative merge |
| `SparseTable` | O(1) query | static range min/max/gcd, idempotent merges only |
| `mpow` / `minv` | O(log e) | modular power and inverse, prime modulus |
| `sieve` | O(n log log n) | smallest prime factor, then O(log x) factorisation |
| `zfunc` | O(n) | prefix matching, substring search, periodicity |
| `dijkstra` | O(m log n) | shortest paths, non-negative weights |
| `ordered_set` | O(log n) | `order_of_key`, `find_by_order`, which `std::set` lacks |
| `fast_map` | ~3x insert | `gp_hash_table`, open addressed |

`SegTree` and `SparseTable` hardcode their merge. Change `merge` and `id`
together or the identity stops being an identity.

## Codeforces judge

```
g++ -Wall -Wextra -Wconversion -static -DONLINE_JUDGE
    -Wl,--stack=268435456 -O2 -std=c++23 program.cpp -lstdc++exp
```

`-O2` and no `-march`, so pragmas are the only way to get more. 256 MB of
stack, so deep recursion is safe and the old "run main on a manual thread"
workaround is dead weight.

Three ways the pragmas go wrong:

- **Below an `#include`.** They only cover what follows, so libstdc++ compiles
  for a different target than your code. That mismatch is the
  `inlining failed in call to always_inline` error out of `allocator.h`.
- **`Ofast`.** It implies `-ffast-math`, which fails to compile with `avx2` on
  GCC 13 and 14. Codeforces runs 14.2. It also contracts `sqrt` into `fma` and
  changes results, so it surfaces as a wrong answer, not a crash. Use `O3`.
- **`optimization`.** The pragma is `optimize`. The misspelling is silently
  ignored, which is why it has survived in copied templates for years.

`avx2` is a bet on judge hardware. Codeforces has it; some judges raise an
illegal instruction instead. Strip that line before reusing the template
elsewhere.

## Anti-hack hashing

`std::hash` on integers is the identity function, so `unordered_map<int,int>`
is trivially hackable: an opponent submits keys that all collide and lookups go
linear. `custom_hash` mixes through splitmix64 with a clock seed, which is not
knowable when the hack is written.

Required on Codeforces. Pointless on LeetCode and HackerRank, which have no
hacking phase.

## LeetCode percentiles

The static initialiser that disables stream sync before `main` is legitimate,
and close to meaningless. It speeds up LeetCode's harness, not your algorithm,
and identical resubmissions already vary by tens of percent:

```cpp
static const int _ = []{ ios_base::sync_with_stdio(false); cin.tie(nullptr); return 0; }();
```

What helps for real: `reserve` before filling, an array instead of a hash map
when the key range is small and known, and `const&` in your own helpers.

The snippet that redirects `cout` to `user.out`, parses the raw test file and
calls `exit(0)` is deliberately absent. `exit(0)` means `Solution` is never
constructed, so the grader reads correct answers for a problem your code did
not run.

## Elsewhere

On HackerRank, input past a few million integers is the one case for a
`getchar_unlocked` reader. It is POSIX, fine on their Linux judge, absent on
Windows toolchains. Old templates write `register int c`; `register` was
removed as a storage class in C++17.

## Sources

- [Codeforces command lines](https://codeforces.com/blog/entry/121114),
  [GCC 14.2 announcement](https://codeforces.com/blog/entry/133046)
- [Caveats of `optimize("Ofast")` with `target("avx2")`](https://codeforces.com/blog/entry/149099)
- [Blowing up `unordered_map`](https://codeforces.com/blog/entry/62393)
- [Faster hash tables with PBDS](https://codeforces.com/blog/entry/60737),
  [order statistics tree](https://codeforces.com/blog/entry/11080)
