"""Facts both tools need, in one place so they cannot disagree.

The index generator and the layout checker used to keep separate extension
lists, which meant a language one of them knew about could still fail the other.
Adding a language is now one line in LANGUAGES.

Anything not listed still counts as a solution and is named after its own
extension, so a new language shows up correctly and never fails CI. The checker
reports it as a notice, which is the nudge to add it here.
"""

from __future__ import annotations

import os

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

LANGUAGES = {
    ".c": "C",
    ".cpp": "C++", ".cc": "C++", ".cxx": "C++",
    ".cs": "C#",
    ".java": "Java",
    ".kt": "Kotlin",
    ".scala": "Scala",
    ".go": "Go",
    ".rs": "Rust",
    ".swift": "Swift",
    ".dart": "Dart",
    ".py": "Python",
    ".rb": "Ruby",
    ".php": "PHP",
    ".js": "JavaScript",
    ".ts": "TypeScript",
    ".sql": "SQL",
    ".sh": "Bash",
    ".pl": "Perl",
    ".hs": "Haskell",
    ".ml": "OCaml",
    ".fs": "F#",
    ".ex": "Elixir", ".exs": "Elixir",
    ".erl": "Erlang",
    ".clj": "Clojure",
    ".rkt": "Racket",
    ".lua": "Lua",
    ".jl": "Julia",
    ".r": "R",
    ".d": "D",
    ".pas": "Pascal",
    ".groovy": "Groovy",
    ".f90": "Fortran", ".f95": "Fortran",
    ".cob": "COBOL",
    ".vb": "Visual Basic",
    ".asm": "Assembly", ".s": "Assembly",
}

IMAGES = {".png", ".jpg", ".jpeg", ".gif", ".webp"}

# Allowed next to a solution but not a solution themselves.
NOTES = {".md", ".txt"}

# Build output and OS clutter. These are the only files worth failing over.
JUNK_NAMES = {".ds_store", "thumbs.db", "desktop.ini"}
JUNK_EXTS = {".exe", ".o", ".obj", ".out", ".class", ".pyc", ".gch", ".pdb", ".ilk"}


def platforms() -> list[str]:
    """Any top-level directory with a problems/ inside it, so adding a platform
    needs no code change."""
    return sorted(
        name for name in os.listdir(REPO)
        if os.path.isdir(os.path.join(REPO, name, "problems"))
    )


def kind(filename: str) -> str:
    """One of: image, notes, junk, source."""
    ext = os.path.splitext(filename)[1].lower()
    if filename.lower() in JUNK_NAMES or ext in JUNK_EXTS:
        return "junk"
    if ext in IMAGES:
        return "image"
    if ext in NOTES:
        return "notes"
    return "source"


def language(filename: str) -> str:
    """Display name for a solution file. Falls back to the extension itself
    rather than "Other", so an unlisted language still says what it is."""
    ext = os.path.splitext(filename)[1].lower()
    if ext in LANGUAGES:
        return LANGUAGES[ext]
    return ext.lstrip(".").upper() or "Unknown"
