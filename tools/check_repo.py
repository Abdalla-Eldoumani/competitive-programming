"""Check that every problem folder follows the repository layout.

The conventions are deliberately loose: a problem is a folder with at least one
source file in it. What this catches is the drift that accumulates silently over
hundreds of commits -- empty folders left behind, filenames that never got
renamed after a copy, and Cyrillic lookalike characters pasted in from a problem
title, which make a problem impossible to find by search.

Usage:
    python tools/check_repo.py
"""

from __future__ import annotations

import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PLATFORMS = ["CodeForces", "HackerRank", "LeetCode"]

KNOWN_SOURCE = {".cpp", ".c", ".sql", ".sh", ".py", ".js", ".rs", ".java"}
KNOWN_IMAGE = {".png", ".jpg", ".jpeg", ".gif", ".webp"}


def main() -> int:
    errors: list[str] = []
    without_statement: list[str] = []
    total = 0

    for platform in PLATFORMS:
        base = os.path.join(REPO, platform, "problems")
        if not os.path.isdir(base):
            errors.append(f"{platform}: missing problems/ directory")
            continue

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

            sources = [f for f in files if os.path.splitext(f)[1].lower() in KNOWN_SOURCE]
            images = [f for f in files if os.path.splitext(f)[1].lower() in KNOWN_IMAGE]
            unknown = [f for f in files if f not in sources and f not in images]

            if not sources:
                errors.append(f"{rel}: no solution file")
            if unknown:
                errors.append(f"{rel}: unrecognised file(s) {', '.join(unknown)}")
            for f in files:
                if " " in f:
                    errors.append(f"{rel}/{f}: filename contains a space")
            if not images:
                without_statement.append(rel)

    print(f"checked {total} problems across {len(PLATFORMS)} platforms")
    if without_statement:
        print(f"\n{len(without_statement)} without a statement screenshot (not an error):")
        for rel in without_statement:
            print(f"  {rel}")

    if errors:
        print(f"\n{len(errors)} problem(s):")
        for err in errors:
            print(f"  {err}")
        return 1

    print("layout is consistent")
    return 0


def _is_latin(char: str) -> bool:
    return char in "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" or 0xC0 <= ord(char) <= 0x24F


if __name__ == "__main__":
    sys.exit(main())
