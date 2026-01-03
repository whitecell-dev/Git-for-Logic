#!/usr/bin/env python3

import subprocess
import sys
from pathlib import Path

def run_abidiff(old_path: Path, new_path: Path):
    """Runs abidiff between two compiled object/shared files."""
    if not old_path.exists() or not new_path.exists():
        print(f"❌ Error: One or both files do not exist: {old_path}, {new_path}")
        sys.exit(1)

    try:
        print(f"🔍 Comparing ABIs:\n  OLD: {old_path}\n  NEW: {new_path}\n")
        result = subprocess.run(
            ["abidiff", str(old_path), str(new_path)],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )

        if result.returncode == 0:
            print("✅ ABI is stable: No differences found.\n")
        else:
            print("🚨 ABI differences detected:\n")
            print(result.stdout)
            sys.exit(2)

    except FileNotFoundError:
        print("❌ abidiff not found. Please install libabigail (e.g., apt install libabigail-dev).")
        sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python guard_abi_checker.py old_version.o new_version.o")
        sys.exit(1)

    old = Path(sys.argv[1])
    new = Path(sys.argv[2])
    run_abidiff(old, new)

