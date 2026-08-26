"""Regenerate the README stats block and the per-platform problem indexes.

Everything is derived: the tree gives the problem list, extensions give the
language, git history gives the solve dates. Nothing is recorded by hand.

    python tools/build_index.py           rewrite the generated files
    python tools/build_index.py --check   fail if they are stale (CI)
"""

from __future__ import annotations

import argparse
import collections
import datetime as dt
import os
import subprocess
import sys
import urllib.parse

import repo

REPO = repo.REPO
PLATFORMS = repo.platforms()

BEGIN = "<!-- BEGIN GENERATED: {} -->"
END = "<!-- END GENERATED: {} -->"

# Each platform's own brand colour, so the badge row is scannable at a glance.
# A platform added later just gets the neutral grey.
BADGE_COLOURS = {"CodeForces": "1f8acb", "LeetCode": "ffa116", "HackerRank": "2ec866"}
DEFAULT_COLOUR = "555"


class Problem:
    def __init__(self, platform: str, name: str, sources: list[str], images: list[str]):
        self.platform = platform
        self.name = name
        self.sources = sources
        self.images = images
        self.solved: dt.date | None = None

    @property
    def path(self) -> str:
        return f"{self.platform}/problems/{self.name}"

    @property
    def languages(self) -> list[str]:
        seen = []
        for src in self.sources:
            lang = repo.language(src)
            if lang not in seen:
                seen.append(lang)
        return seen

    @property
    def lines(self) -> int:
        total = 0
        for src in self.sources:
            with open(os.path.join(REPO, self.path, src), encoding="utf-8", errors="replace") as fh:
                total += sum(1 for line in fh if line.strip())
        return total


def collect() -> list[Problem]:
    problems = []
    for platform in PLATFORMS:
        base = os.path.join(REPO, platform, "problems")
        if not os.path.isdir(base):
            continue
        for name in sorted(os.listdir(base), key=str.lower):
            full = os.path.join(base, name)
            if not os.path.isdir(full):
                continue
            files = sorted(os.listdir(full))
            images = [f for f in files if repo.kind(f) == "image"]
            sources = [f for f in files if repo.kind(f) == "source"]
            if sources:
                problems.append(Problem(platform, name, sources, images))
    return problems


def solved_dates() -> dict[str, dt.date]:
    """Map each problem directory to the date its first file landed in git.

    Renames are followed so that tidying a filename later does not reset the
    date a problem was actually solved.
    """
    out = subprocess.run(
        ["git", "-c", "core.quotepath=false", "log", "--reverse", "-M",
         "--name-status", "--format=C|%ct"],
        cwd=REPO, capture_output=True, encoding="utf-8", errors="replace", check=True,
    ).stdout

    dates: dict[str, dt.date] = {}
    stamp = None
    for line in out.splitlines():
        if line.startswith("C|"):
            stamp = dt.datetime.fromtimestamp(int(line[2:]), dt.timezone.utc).date()
            continue
        if not line.strip() or stamp is None:
            continue
        parts = line.split("\t")
        status = parts[0]
        if status.startswith("R") and len(parts) >= 3:
            old, new = os.path.dirname(parts[1]), os.path.dirname(parts[2])
            if old in dates:
                dates.setdefault(new, dates[old])
            continue
        if status.startswith("A") and len(parts) >= 2:
            folder = os.path.dirname(parts[1])
            if folder and folder not in dates:
                dates[folder] = stamp
    return dates


def link(path: str, label: str) -> str:
    return f"[{label}]({urllib.parse.quote(path)})"


def platform_index(platform: str, problems: list[Problem]) -> str:
    rows = [p for p in problems if p.platform == platform]
    lines = [
        f"# {platform}",
        "",
        f"{len(rows)} solved. Each folder holds the solution and a screenshot of the",
        "problem statement, so the repository reads on its own without visiting the site.",
        "",
        "| # | Problem | Solution | Language | Solved |",
        "|--:|:--------|:---------|:---------|:-------|",
    ]
    for i, p in enumerate(rows, 1):
        sources = ", ".join(
            link(f"problems/{p.name}/{s}", f"`{s}`") for s in p.sources
        )
        solved = p.solved.isoformat() if p.solved else "-"
        lines.append(
            f"| {i} | {link(f'problems/{p.name}', p.name)} | {sources} "
            f"| {', '.join(p.languages)} | {solved} |"
        )
    lines.append("")
    return "\n".join(lines)


def histogram(problems: list[Problem], width: int = 40) -> list[str]:
    per_month = collections.Counter(
        p.solved.strftime("%Y-%m") for p in problems if p.solved
    )
    if not per_month:
        return []
    peak = max(per_month.values())
    lines = []
    for month in _months_between(min(per_month), max(per_month)):
        count = per_month.get(month, 0)
        # Months with no activity are drawn as gaps rather than dropped, so a
        # break in the chart reads as a break rather than as missing data.
        bar = "#" * max(1, round(count / peak * width)) if count else ""
        lines.append(f"{month}  {bar} {count}".rstrip())
    return lines


def _months_between(first: str, last: str) -> list[str]:
    year, month = (int(x) for x in first.split("-"))
    end_year, end_month = (int(x) for x in last.split("-"))
    out = []
    while (year, month) <= (end_year, end_month):
        out.append(f"{year:04d}-{month:02d}")
        year, month = (year + 1, 1) if month == 12 else (year, month + 1)
    return out


def stats_block(problems: list[Problem]) -> str:
    by_platform = collections.Counter(p.platform for p in problems)
    by_language: collections.Counter[str] = collections.Counter()
    for p in problems:
        for lang in p.languages:
            by_language[lang] += 1

    total = len(problems)
    badges = [f"![Problems](https://img.shields.io/badge/problems-{total}-555)"]
    for platform in PLATFORMS:
        count = by_platform.get(platform, 0)
        colour = BADGE_COLOURS.get(platform, DEFAULT_COLOUR)
        badges.append(
            f"![{platform}](https://img.shields.io/badge/{platform}-{count}-{colour})"
        )

    lines = [
        " ".join(badges),
        "",
        "| Platform | Solved | Index |",
        "|:---------|-------:|:------|",
    ]
    for platform in PLATFORMS:
        count = by_platform.get(platform, 0)
        lines.append(f"| {platform} | {count} | [browse]({platform}/README.md) |")
    lines += [f"| **Total** | **{total}** | |", ""]

    lines.append("Languages: " + ", ".join(
        f"{lang} ({count})" for lang, count in by_language.most_common()
    ))

    dated = [p.solved for p in problems if p.solved]
    if dated:
        span = f"{min(dated).isoformat()} to {max(dated).isoformat()}"
        total_lines = sum(p.lines for p in problems)
        lines += [
            "",
            f"Span: {span}. {total_lines:,} lines of solution code.",
        ]

    chart = histogram(problems)
    if chart:
        lines += ["", "```", "Problems solved per month", ""] + chart + ["```"]

    return "\n".join(lines)


def splice(text: str, marker: str, body: str) -> str:
    begin, end = BEGIN.format(marker), END.format(marker)
    if begin not in text or end not in text:
        raise SystemExit(f"README is missing the {marker} markers")
    head = text.split(begin)[0]
    tail = text.split(end)[1]
    return f"{head}{begin}\n{body}\n{end}{tail}"


def write(path: str, content: str, check: bool) -> bool:
    full = os.path.join(REPO, path)
    current = None
    if os.path.exists(full):
        with open(full, encoding="utf-8") as fh:
            current = fh.read()
    if current == content:
        return False
    if check:
        print(f"out of date: {path}")
        return True
    os.makedirs(os.path.dirname(full), exist_ok=True)
    with open(full, "w", encoding="utf-8", newline="\n") as fh:
        fh.write(content)
    print(f"wrote {path}")
    return True


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true",
                        help="exit non-zero if generated files need regenerating")
    args = parser.parse_args()

    problems = collect()
    dates = solved_dates()
    for p in problems:
        p.solved = dates.get(p.path)

    stale = False
    for platform in PLATFORMS:
        stale |= write(f"{platform}/README.md", platform_index(platform, problems), args.check)

    readme = os.path.join(REPO, "README.md")
    with open(readme, encoding="utf-8") as fh:
        text = fh.read()
    stale |= write("README.md", splice(text, "STATS", stats_block(problems)), args.check)

    if stale and args.check:
        print("\nRun: python tools/build_index.py")
        return 1
    if not stale:
        print(f"up to date ({len(problems)} problems)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
