"""Network-free regression tests for release-package discovery.

Run: py -3 tools/friends/test_resolve_package.py
These are filesystem/selection tests, not game, emulator, or GitHub-upload tests.
"""
from __future__ import annotations

import contextlib
import io
import json
import os
import sys
import tempfile
import unittest
from pathlib import Path

sys.dont_write_bytecode = True
from resolve_package import PackageSelectionError, main, resolve_package, write_selection


CURRENT = "e33650e579767739b7b13d7bdd7800e0cf73a1cb"
OLD = "366699b" + "0" * 33


class PackageSelectionTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="rogue publisher tests ")
        self.repo = Path(self.temp.name).resolve()
        (self.repo / "dist").mkdir()

    def tearDown(self):
        self.temp.cleanup()

    def manifest(self, folder: str, commit: str = CURRENT, **fields):
        directory = self.repo / folder
        directory.mkdir(parents=True, exist_ok=True)
        path = directory / "build-manifest.json"
        path.write_text(json.dumps({"git_commit": commit, **fields}), encoding="utf-8")
        return path

    def test_legacy_root_package_still_works(self):
        path = self.manifest("dist")
        self.assertEqual(resolve_package(self.repo, CURRENT)["manifest_file"], str(path))

    def test_versioned_package_is_discovered(self):
        path = self.manifest("dist/v0.2.0")
        self.assertEqual(resolve_package(self.repo, CURRENT)["package_dir"], str(path.parent))

    def test_reported_failure_stale_root_and_fresh_v020(self):
        self.manifest("dist", OLD)
        fresh = self.manifest("dist/v0.2.0")
        result = resolve_package(self.repo, CURRENT)
        self.assertEqual(result["manifest_file"], str(fresh))
        self.assertEqual(result["git_commit"], CURRENT)

    def test_newer_timestamp_does_not_override_current_commit(self):
        stale = self.manifest("dist/v99.0.0", OLD)
        current = self.manifest("dist/v0.2.0")
        os.utime(current, (1000, 1000))
        os.utime(stale, (2000, 2000))
        self.assertEqual(resolve_package(self.repo, CURRENT)["manifest_file"], str(current))

    def test_future_versions_need_no_script_changes(self):
        self.manifest("dist", OLD)
        self.manifest("dist/v0.2.0", OLD)
        path = self.manifest("dist/v0.3.0-rc.1")
        self.assertEqual(resolve_package(self.repo, CURRENT)["manifest_file"], str(path))

    def test_wrong_commit_only_is_rejected(self):
        self.manifest("dist/v0.2.0", OLD)
        with self.assertRaisesRegex(PackageSelectionError, "No release package matches"):
            resolve_package(self.repo, CURRENT)

    def test_two_current_packages_require_explicit_choice(self):
        self.manifest("dist")
        self.manifest("dist/v0.2.0")
        with self.assertRaisesRegex(PackageSelectionError, "Multiple packages"):
            resolve_package(self.repo, CURRENT)

    def test_explicit_current_version_resolves_ambiguity(self):
        self.manifest("dist")
        path = self.manifest("dist/v0.2.0")
        result = resolve_package(self.repo, CURRENT, "dist/v0.2.0")
        self.assertEqual(result["manifest_file"], str(path))

    def test_explicit_absolute_directory(self):
        path = self.manifest("dist/v0.2.0")
        self.assertEqual(resolve_package(self.repo, CURRENT, path.parent)["manifest_file"], str(path))

    def test_explicit_stale_package_does_not_fall_back(self):
        self.manifest("dist", OLD)
        self.manifest("dist/v0.2.0")
        with self.assertRaisesRegex(PackageSelectionError, "selected package does not match"):
            resolve_package(self.repo, CURRENT, "dist")

    def test_explicit_outside_dist_is_rejected(self):
        self.manifest("build/release-staging")
        with self.assertRaisesRegex(PackageSelectionError, "inside this repository"):
            resolve_package(self.repo, CURRENT, "build/release-staging")

    def test_explicit_missing_directory_is_rejected(self):
        with self.assertRaisesRegex(PackageSelectionError, "does not exist"):
            resolve_package(self.repo, CURRENT, "dist/no-such-version")

    def test_invalid_commit_is_rejected(self):
        with self.assertRaisesRegex(PackageSelectionError, "40-character"):
            resolve_package(self.repo, "e33650e")

    def test_missing_dist_is_rejected(self):
        (self.repo / "dist").rmdir()
        with self.assertRaisesRegex(PackageSelectionError, "does not exist"):
            resolve_package(self.repo, CURRENT)

    def test_no_manifests_is_rejected(self):
        with self.assertRaisesRegex(PackageSelectionError, "No release package matches"):
            resolve_package(self.repo, CURRENT)

    def test_malformed_root_does_not_hide_valid_version(self):
        (self.repo / "dist/build-manifest.json").write_text("{broken", encoding="utf-8")
        path = self.manifest("dist/v0.2.0")
        self.assertEqual(resolve_package(self.repo, CURRENT)["manifest_file"], str(path))

    def test_nonobject_and_missing_commit_manifests_are_rejected(self):
        for raw in ("[]", "null", "{}", '{"git_commit":42}', '{"git_commit":"abc"}'):
            with self.subTest(raw=raw):
                (self.repo / "dist/build-manifest.json").write_text(raw, encoding="utf-8")
                with self.assertRaises(PackageSelectionError):
                    resolve_package(self.repo, CURRENT)

    def test_utf8_bom_and_literal_brackets_in_directory(self):
        path = self.manifest("dist/v0.2.0 [test]")
        path.write_text(json.dumps({"git_commit": CURRENT}), encoding="utf-8-sig")
        self.assertEqual(resolve_package(self.repo, CURRENT)["manifest_file"], str(path))

    def test_commit_case_and_whitespace_are_normalized(self):
        self.manifest("dist/v0.2.0", " " + CURRENT.upper() + "\n")
        self.assertEqual(resolve_package(self.repo, CURRENT.upper())["git_commit"], CURRENT)

    def test_arbitrary_nested_staging_is_not_automatically_selected(self):
        self.manifest("dist/archive/stale-copy")
        with self.assertRaises(PackageSelectionError):
            resolve_package(self.repo, CURRENT)

    def test_write_selection_is_utf8_and_leaves_no_temp_files(self):
        path = self.manifest("dist/v0.2.0")
        output = self.repo / "build/friends-launcher/package-selection.json"
        write_selection(output, resolve_package(self.repo, CURRENT))
        self.assertEqual(json.loads(output.read_text())["manifest_file"], str(path))
        self.assertEqual(list(output.parent.glob("*.tmp")), [])

    def test_cli_writes_selection_for_current_package(self):
        self.manifest("dist", OLD)
        path = self.manifest("dist/v0.2.0")
        output = self.repo / "build/friends-launcher/package-selection.json"
        with contextlib.redirect_stdout(io.StringIO()):
            status = main(["--repo", str(self.repo), "--commit", CURRENT, "--write-selection", str(output)])
        self.assertEqual(status, 0)
        self.assertEqual(json.loads(output.read_text())["manifest_file"], str(path))

    def test_cli_failure_does_not_write_a_selection(self):
        self.manifest("dist", OLD)
        output = self.repo / "build/selection.json"
        errors = io.StringIO()
        with contextlib.redirect_stderr(errors):
            status = main(["--repo", str(self.repo), "--commit", CURRENT, "--write-selection", str(output)])
        self.assertEqual(status, 2)
        self.assertFalse(output.exists())
        self.assertIn("Observed manifests", errors.getvalue())
        self.assertIn(OLD, errors.getvalue())
        self.assertIn("Nothing was uploaded", errors.getvalue())

    def test_cli_cannot_overwrite_source_or_release_manifest(self):
        path = self.manifest("dist/v0.2.0")
        original = path.read_bytes()
        with contextlib.redirect_stderr(io.StringIO()):
            status = main(["--repo", str(self.repo), "--commit", CURRENT, "--write-selection", str(path)])
        self.assertEqual(status, 2)
        self.assertEqual(path.read_bytes(), original)

    def test_selection_does_not_modify_old_or_current_manifests(self):
        old = self.manifest("dist", OLD)
        new = self.manifest("dist/v0.2.0")
        before = {path: path.read_bytes() for path in (old, new)}
        resolve_package(self.repo, CURRENT)
        self.assertEqual(before, {path: path.read_bytes() for path in before})


if __name__ == "__main__":
    unittest.main(verbosity=2)
