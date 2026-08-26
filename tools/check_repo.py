"""Check that every problem folder follows the repository layout.

A problem is a folder with at least one source file. This catches the drift that
accumulates silently over hundreds of commits: empty folders, filenames left
behind by a copy, and Cyrillic lookalikes pasted in from a problem title that
make a problem unsearchable.

A solution in a language not yet listed in repo.py is a notice, not an error.
Adding a language should never be the thing that turns CI red.
"""

from __future__ import annotations

import os
import sys

import repo

PLATFORMS = repo.platforms()


def main() -> int:
    errors: list[str] = []
    without_statement: list[str] = []
    unlisted: list[str] = []
    total = 0

    if not PLATFORMS:
        print("no platform directories found; expected <Platform>/problems/")
        return 1

    for platform in PLATFORMS:
        base = os.path.join(repo.REPO, platform, "problems")
        for name in sorted(os.listdir(base)):
            full = os.path.join(base, name)
            if not os.path.isdir(full):
                errors.append(f"{platform}/problems/{name}: stray file outside a problem folder")
                continue

            rel = f"{platform}/problems/{name}"
            total += 1

            # A Cyrillic 'c' reads identically to a Latin one but breaks every
            # search for the problem. Titles are ASCII; punctuation is not.
            for char in name:
                if ord(char) > 127 and char.isalpha() and not _is_latin(char):
                    errors.append(f"{rel}: non-Latin lookalike {char!r} (U+{ord(char):04X}) in folder name")
                    break

            files = sorted(os.listdir(full))
            if not files:
                errors.append(f"{rel}: empty folder")
                continue

            sources, images = [], []
            for f in files:
                what = repo.kind(f)
                if what == "junk":
                    errors.append(f"{rel}/{f}: build output or OS clutter, should not be committed")
                elif what == "image":
                    images.append(f)
                elif what == "source":
                    sources.append(f)
                    if os.path.splitext(f)[1].lower() not in repo.LANGUAGES:
                        unlisted.append(f"{rel}/{f}")
                if " " in f:
                    errors.append(f"{rel}/{f}: filename contains a space")

            if not sources:
                errors.append(f"{rel}: no solution file")
            if not images:
                without_statement.append(rel)

    print(f"checked {total} problems across {len(PLATFORMS)} platforms")
    _notice(without_statement, "without a statement screenshot")
    _notice(unlisted, "in a language not yet listed in tools/repo.py, so named "
                      "after the extension")

    if errors:
        print(f"\n{len(errors)} problem(s):")
        for err in errors:
            print(f"  {err}")
        return 1

    print("layout is consistent")
    return 0


def _notice(items: list[str], what: str) -> None:
    if not items:
        return
    print(f"\n{len(items)} {what} (not an error):")
    for item in items:
        print(f"  {item}")


def _is_latin(char: str) -> bool:
    """Latin-1 Supplement through Latin Extended-B, so an accented title is fine
    but Cyrillic and Greek lookalikes are not."""
    return 0xC0 <= ord(char) <= 0x24F


if __name__ == "__main__":
    sys.exit(main())
