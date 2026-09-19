"""Locate the package for an exact source commit without trusting folder timestamps.

Supports dist/build-manifest.json and dist/<version>/build-manifest.json.
Only selects metadata; Publish-TestBuild.ps1 still verifies the selected patch,
reconstructed-image hash, local output image, and clean Git worktree before upload.
No network, Git, emulator, or third-party Python packages are used here.
"""
from __future__ import annotations

import argparse
import json
import os
import re
import sys
import tempfile
from pathlib import Path
from typing import Any


class PackageSelectionError(ValueError):
    """The package cannot be selected unambiguously for the requested commit."""


def resolve_package(
    repo_path: str | Path,
    commit: str,
    package_directory: str | Path | None = None,
) -> dict[str, str]:
    """Return one current-commit package, never the newest-looking stale folder."""
    commit = commit.strip().lower()
    if not re.fullmatch(r"[0-9a-f]{40}", commit):
        raise PackageSelectionError("Expected the full 40-character Git commit SHA.")

    repo = Path(repo_path).expanduser().resolve()
    dist = repo / "dist"
    if not dist.is_dir():
        raise PackageSelectionError(
            f"Package directory does not exist: {dist}. Run the release package command first."
        )
    dist = dist.resolve()

    if package_directory:
        requested = Path(package_directory).expanduser()
        if not requested.is_absolute():
            requested = repo / requested
        requested = requested.resolve()
        if not requested.is_relative_to(dist):
            raise PackageSelectionError("-PackageDirectory must point inside this repository's dist directory.")
        if not requested.is_dir():
            raise PackageSelectionError(f"Package directory does not exist: {requested}")
        candidates = [requested / "build-manifest.json"]
    else:
        # Inspect the legacy layout and immediate version directories. Do not
        # walk caches, staging directories, or arbitrary nested release content.
        candidates = [dist / "build-manifest.json"]
        candidates.extend(
            child / "build-manifest.json"
            for child in sorted(dist.iterdir(), key=lambda p: p.name.casefold())
            if child.is_dir() and not child.is_symlink()
        )

    matches: list[dict[str, str]] = []
    observations: list[str] = []
    for manifest in candidates:
        if not manifest.is_file():
            if package_directory:
                observations.append(f"{manifest}: missing")
            continue
        # A selection must not escape the dist tree through a linked manifest.
        if not manifest.resolve().is_relative_to(dist):
            observations.append(f"{manifest}: linked outside dist; ignored")
            continue
        try:
            if manifest.stat().st_size > 8 * 1024 * 1024:
                raise ValueError("manifest exceeds 8 MiB")
            meta: Any = json.loads(manifest.read_text(encoding="utf-8-sig"))
            if not isinstance(meta, dict):
                raise ValueError("manifest must be a JSON object")
            recorded = meta.get("git_commit")
            if not isinstance(recorded, str):
                raise ValueError("git_commit is missing or not a string")
            recorded = recorded.strip().lower()
            if not re.fullmatch(r"[0-9a-f]{40}", recorded):
                raise ValueError("git_commit must be a full 40-character SHA")
        except (OSError, UnicodeError, ValueError) as error:
            observations.append(f"{manifest}: invalid ({error})")
            continue

        observations.append(f"{manifest}: commit {recorded}")
        if recorded == commit:
            matches.append({
                "package_dir": str(manifest.parent),
                "manifest_file": str(manifest),
                "git_commit": recorded,
            })

    if not matches:
        details = "\n  ".join(observations) or "No build-manifest.json files found."
        if package_directory:
            summary = f"The selected package does not match current commit {commit}."
        else:
            summary = (
                f"No release package matches current commit {commit}.\n"
                "Searched dist/build-manifest.json and dist/<version>/build-manifest.json."
            )
        raise PackageSelectionError(f"{summary}\nObserved manifests:\n  {details}")
    if len(matches) != 1:
        folders = "\n  ".join(item["package_dir"] for item in matches)
        raise PackageSelectionError(
            f"Multiple packages match current commit {commit}:\n  {folders}\n"
            'Choose explicitly with -PackageDirectory "dist/<intended-version>". '
            "The publisher will not guess by version name or modification time."
        )
    return matches[0]


def write_selection(path: Path, result: dict[str, str]) -> None:
    """Atomically write the small selection file consumed by PowerShell."""
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary: Path | None = None
    try:
        with tempfile.NamedTemporaryFile(
            mode="w", encoding="utf-8", newline="\n", prefix=path.name + ".", suffix=".tmp",
            dir=path.parent, delete=False,
        ) as handle:
            temporary = Path(handle.name)
            json.dump(result, handle, indent=2)
            handle.write("\n")
            handle.flush()
            os.fsync(handle.fileno())
        os.replace(temporary, path)
    finally:
        if temporary is not None:
            temporary.unlink(missing_ok=True)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo", required=True, type=Path)
    parser.add_argument("--commit", required=True)
    parser.add_argument("--package-dir", default=None, type=Path)
    parser.add_argument("--write-selection", required=True, type=Path)
    args = parser.parse_args(argv)
    try:
        repo = args.repo.expanduser().resolve()
        selection_file = args.write_selection.expanduser()
        if not selection_file.is_absolute():
            selection_file = repo / selection_file
        selection_file = selection_file.resolve()
        if not selection_file.is_relative_to((repo / "build").resolve()):
            raise PackageSelectionError("The selection JSON must be written under the repository's build directory.")
        result = resolve_package(repo, args.commit, args.package_dir)
        write_selection(selection_file, result)
        print(f"Selected package directory: {result['package_dir']}")
        print(f"Selected package commit: {result['git_commit']}")
        return 0
    except (PackageSelectionError, OSError) as error:
        print(f"ERROR: {error}", file=sys.stderr)
        print("Nothing was uploaded. Do not bypass the commit/hash checks; re-run packaging for current source.", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
