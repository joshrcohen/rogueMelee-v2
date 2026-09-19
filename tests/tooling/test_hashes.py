import hashlib
from pathlib import Path
import tempfile
import unittest
from tools.lib.hash import file_hash
from tools.lib.iso import verify, read_dol


class HashTests(unittest.TestCase):
    def test_hash_and_wrong_image_leave_source_unchanged(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            image = root / 'wrong.iso'
            image.write_bytes(b'wrong image')
            self.assertEqual(file_hash(image), hashlib.sha256(b'wrong image').hexdigest())
            with self.assertRaises(ValueError):
                verify(image, root)
            self.assertEqual(image.read_bytes(), b'wrong image')
            self.assertFalse((root / 'build/source-manifest.json').exists())

    def test_truncated_image(self):
        with tempfile.TemporaryDirectory() as tmp:
            image = Path(tmp) / 'short.iso'
            image.write_bytes(b'GALE01')
            with self.assertRaises(ValueError):
                read_dol(image)
