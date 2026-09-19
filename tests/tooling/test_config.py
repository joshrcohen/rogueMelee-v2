import os
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch
from tools.lib.config import load


class ConfigTests(unittest.TestCase):
    def test_environment_overrides_file(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'config').mkdir()
            (root / 'config/local.toml').write_text('[paths]\nmelee_iso="old.iso"\n[build]\njobs=2\n')
            with patch.dict(os.environ, {'MELEE_ISO_PATH':'new.iso', 'ROGUEMELEE_BUILD_JOBS':'4'}):
                result = load(root)
            self.assertEqual(result['paths']['melee_iso'], 'new.iso')
            self.assertEqual(result['build']['jobs'], 4)

    def test_invalid_jobs(self):
        with tempfile.TemporaryDirectory() as tmp, patch.dict(os.environ, {'ROGUEMELEE_BUILD_JOBS':'0'}):
            with self.assertRaises(ValueError):
                load(Path(tmp))
