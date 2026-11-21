#!/usr/bin/env python3
"""Fail when game files, compiled output or local-only data would be committed.

Checks every file git tracks or would add (default), or only staged content (--staged).
Rules: anything under local/; executable, object, disc and Ghidra project types by name;
PE, ELF, x86 COFF and Unreal package content by magic bytes; files over 5 MB.
"""
import argparse
from pathlib import PurePosixPath
import re
import subprocess
import sys

LIMIT = 5 * 1024 * 1024
NAMES = re.compile(r"\.(exe|dll|obj|lib|elf|iso|bin|cue|pdb|gpr|gzf|u|utx|usx|ukx|uax|umx|sdc|int)$"
                   r"|^[sc][cl][eu][sm]_\d{3}\.\d{2}$", re.IGNORECASE)


def problems(path, data):
    found = []
    parts = PurePosixPath(path).parts
    if "local" in parts[:-1]:
        found.append("local-only folder")
    if any(part.lower().endswith(".rep") for part in parts[:-1]) or NAMES.search(parts[-1]):
        found.append("binary or game file type")
    if data[:2] == b"MZ":
        found.append("Windows executable content")
    if data[:4] == b"\x7fELF":
        found.append("ELF content")
    if data[:2] == b"\x4c\x01" and len(data) >= 20:
        found.append("x86 COFF object content")
    if data[:4] == b"\xc1\x83\x2a\x9e":
        found.append("Unreal package content")
    if len(data) > LIMIT:
        found.append(f"larger than {LIMIT // (1024 * 1024)} MB")
    return found


def git(*args):
    return subprocess.run(["git", *args], check=True, capture_output=True).stdout


def candidates(staged):
    if staged:
        names = git("diff", "--cached", "--name-only", "--diff-filter=ACMRT", "-z").split(b"\0")
        return [(n.decode(), git("show", ":" + n.decode())) for n in names if n]
    names = git("ls-files", "--cached", "--others", "--exclude-standard", "-z").split(b"\0")
    out = []
    for n in names:
        if n:
            try:
                out.append((n.decode(), open(n.decode(), "rb").read()))
            except FileNotFoundError:
                pass
    return out


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--staged", action="store_true", help="check staged content only")
    args = parser.parse_args()
    bad = [(path, issue) for path, data in candidates(args.staged) for issue in problems(path, data)]
    for path, issue in bad:
        print(f"{path}: {issue}")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
